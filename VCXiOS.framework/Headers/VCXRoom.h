@import WebRTC;
#import <Foundation/Foundation.h>
#import "VCXClient.h"
#import "VCXSignalingChannel.h"
#import "VCXStream.h"
#import "VCXRoomStatsProtocol.h"
@class VCXRoom;
@class Client;

/**
 @enum VCXRoomStatus
 */
typedef NS_ENUM(NSInteger, VCXRoomStatus) {
    VCXRoomStatusReady,
    VCXRoomStatusConnected,
    VCXRoomStatusDisconnected,
    VCXRoomStatusError
};

/**
 @enum VCXRoomErrorStatus
 */
typedef NS_ENUM(NSInteger, VCXRoomErrorStatus) {
    VCXRoomErrorUnknown,
    /// A generic error that comes from an VCXClient
    VCXRoomErrorClient,
    VCXRoomErrorClientFailedSDP,
    /// A generic error that comes from VCXSignalingChannel
    VCXRoomErrorSignaling
};

///-----------------------------------
/// @name Protocols
///-----------------------------------

/**
 VCXRoomDelegate
 
 Will fire events related with VCXRoom state change.
 */

@protocol VCXRoomDelegate <NSObject>
@optional
/**
 Fired when server sent the streamId of the subscribed stream.
 
 @param room Instance of the room where event happen.
 @param stream The subscribed Stream object.
 
 */
- (void)room:(VCXRoom *)room didSubscribeStream:(VCXStream *)stream;

/**
 Fired when server has succesfully unsubscribed a stream.
 
 @param room Instance of the room where event happen.
 @param stream The unSubscribed Stream object.
 
 */
- (void)room:(VCXRoom *)room didUnSubscribeStream:(VCXStream *)stream;

/**
 Fired when server sent the streamId of the published stream.
 
 @param room Instance of the room where event happen.
 @param stream VCXStream being published.
 
 */
- (void)room:(VCXRoom *)room didPublishStream:(VCXStream *)stream;

/**
 Fired when server ACK to unpublish the requested stream by VCXRoom:unpublish.
 After this method is called the Room will close and nilify the publishing
 client. You need to unreference the publishing stream from your side to let
 the object be deallocated.
 
 @param stream The stream being unpublished.
 */
- (void)room:(VCXRoom *)room didUnpublishStream:(VCXStream *)stream;

/**
 Fired when server sent the recordingId of a stream being published and
 recorded.
 
 @param room Instance of the room where event happen.
 @param stream String representing the Id of the stream being recorded.
 @param recordingId String representing the Id of the recording of the stream.
 @param recordingDate moment when the server started to record the stream.
 
 */
- (void)room:(VCXRoom *)room didStartRecordingStream:(VCXStream *)stream
withRecordingId:(NSString *)recordingId
recordingDate:(NSDate *)recordingDate;
/**
 Fired when server failed to start recording the stream.
 
 @param room Instance of the room where event happen.
 @param stream String representing the Id of the stream being recorded.
 @param errorMsg The error message sent by the server.
 
 */
//- (void)room:(VCXRoom *)room didFailStartRecordingStream:(VCXStream *)stream
//withErrorMsg:(NSString *)errorMsg;


//delegate method when recording start successful
-(void)startRecordingEvent:(NSArray *)response;

//when recording fails.
//-(void)recordingDidFail:(NSString *)response;

//delegate method when recording stop successful
-(void)stopRecordingEvent:(NSArray *)response;

//when recording stop fails.
//-(void)recordingDidStopFail:(NSString *)response;

/**
 Fired when signaling channel connected with VCX Room.
 
 @param room Instance of the room where event happen.
 
 roomMetadata sample:
 {
 defaultVideoBW = 300;
 iceServers = (
 {
 url = "stun:stun.l.google.com:19302";
 },
 {
 credential = secret;
 url = "turn:xxx.xxx.xxx.xxx:443";
 username = me;
 }
 );
 id = 591df649e29e562067143117;
 maxAudioBW = 64;
 maxVideoBW = 300;
 streams =(
 {
 audio = 1;
 id = 208339986973492030;
 video = 1;
 }
 );
 }
 
 */
- (void)room:(VCXRoom *)room didConnect:(NSDictionary *)roomMetadata;

- (void)roomDidDisconnected:(VCXRoomStatus)status;

/**
 Fired each time there is an error with the room.
 It doesn't mean the room has been disconnected. For example you could receive
 this message when one of the streams subscribed did fail for some reason.
 
 @param room Instance of the room where event happen.
 @param status Status constant
 @param reason Text explaining the error. (Not always available)
 
 */
- (void)room:(VCXRoom *)room
    didError:(VCXRoomErrorStatus)status
      reason:(NSString *)reason;

- (void)room:(VCXRoom *)room
didRecoonect:(VCXRoomErrorStatus)status
      reason:(NSString *)reason;



/**
 Fired each time the room changed his state.
 
 @param room Instance of the room where event happen.
 @param status VCXRoomStatus value.
 
 */
- (void)room:(VCXRoom *)room didChangeStatus:(VCXRoomStatus)status;

/**
 Event fired once a new stream has been added to the room.
 
 It is up to you to subscribe that stream or not.
 It is worth to notice that your published stream will not be notified
 by this method, use VCXRoomDelegate:didPublishStream: instead.
 
 @param room Instance of the room where event happen.
 @param stream VCXStream object (not subscribed yet), that were just added
 to the room.
 */
- (void)room:(VCXRoom *)room didAddedStream:(VCXStream *)stream;

/**
 Fired when a stream in a room has been removed, not necessary the
 stream was being consumed/subscribed.
 
 @param room Instance of the room where event happen.
 @param stream The removed stream.
 
 @discusion After this method return the stream will be destroyed.
 
 */
- (void)room:(VCXRoom *)room didRemovedStream:(VCXStream *)stream;

/**
 Fired when a data stream is received.
 
 @param room Instance of the room where event happen.
 @param stream The VCXStream received from.
 @param data stream message received.
 
 */
- (void)room:(VCXRoom *)room didReceiveData:(NSDictionary *)data
  fromStream:(VCXStream *)stream;



/**
 Fired when stream attribute updated.
 
 @param room Instance of the room where event happen.
 @param stream The stream that updated his attributes.
 
 @discusion Look VCXStream:streamAttributes to know which.
 
 */
- (void)room:(VCXRoom *)room didUpdateAttributesOfStream:(VCXStream *)stream;

//On Logs upload success
-(void)logsUploadedSuccess:(NSString *)message;

//On Logs uploaded failure
-(void)logsUploadedFailure:(NSString *)message;

//-(void)onAudioEvents:(NSString *)message;
//-(void)onErrorAudioEvents:(NSException *)error;

#pragma mark- ChairControl
#pragma mark- CC
- (void)didFloorRequested:(NSArray *)Data;

- (void)didGrantFloorRequested:(NSArray *)Data;
// Grant

- (void)didDenyFloorRequested:(NSArray *)Data;
// Deny

- (void)didReleaseFloorRequested:(NSArray *)Data;
//Release

#pragma mark- ChairControl - Moderator Delegate

- (void)didFloorRequestReceived:(NSArray *)Data;

- (void)didProcessFloorRequested:(NSArray *)Data;


#pragma mark-  HardMute Delegate

//Moderator Delegates:
- (void)didMutedAllUser:(NSArray *)Data;
- (void)didUnMutedAllUser:(NSArray *)Data;

//Paricipant Delegates:
- (void)didHardMutedAll:(NSArray *)Data;
//- (void)didHardUnMuteAllUser:(NSArray *)Data;

//Audio Mute/Unmute single user
//Moderator Delegates
- (void)didMutedSingleUser:(NSArray *)Data;
- (void)didUnMutedSingleUser:(NSArray *)Data;

//Paricipant Delegates:
- (void)didHardMutedSingleUser:(NSArray *)Data;
//- (void)didHardUnMuteSingleUser:(NSArray *)Data;

//UserList Delegate
-(void)room:(VCXRoom *)room userDidJoined:(NSArray *)Data;
-(void)room:(VCXRoom *)room userDidDisconnected:(NSArray *)Data;

// Raish hand and approve hand delegate
- (void)room:(VCXRoom *)room ChairControlStates:(NSMutableDictionary *)data;

#pragma mark- recording Participant delegate
-(void)roomRecordOn:(NSArray *)Data;
-(void)roomRecordOff:(NSArray *)Data;

@end

///-----------------------------------
/// @name Interface Declaration
///-----------------------------------

/*
 Interface responsable of publshing/consuming streams in a given VCXRoom.
 */
@interface VCXRoom : NSObject <VCXSignalingChannelRoomDelegate, VCXClientDelegate>

///-----------------------------------
/// @name Initializers
///-----------------------------------

/**
 Create a VCXRoom instance with a given *VCX* token and VCXRoomDelegate.
 
 Encoded token sample:
 
 {
 @"tokenId":@"559ee50ec55db4935dd0d865",
 @"host":@"example.com:443",
 @"secure":@TRUE,
 @"signature":@"MDA3MDQxZTZkMWZlOWIwNTA0NmYzZjU1NmIzODQyNWUzNzIyZTJhOA=="
 }
 
 @param encodedToken Base64 encoded string.
 @param delegate VCXRoomDelegate instance for this room.
 @param factory RTCPeerConnectionFactory instance for this room.
 
 @return instancetype
 
 */
- (instancetype)initWithEncodedToken:(NSString *)encodedToken delegate:(id<VCXRoomDelegate>)delegate
                      andPeerFactory:(RTCPeerConnectionFactory *)factory;

/**
 Create an VCXRoom with the given VCXRoomDelegate.
 
 Notice that if initialize VCXRoom like this, you will never be able to
 publish/subscribe streams without first call method connectWithEncodedToken:
 method.
 @see connectWithEncodedToken:
 
 @param roomDelegate VCXRoomDelegate instance for this room.
 @param factory RTCPeerConnectionFactory instance for this room.
 
 @return instancetype
 */
- (instancetype)initWithDelegate:(id<VCXRoomDelegate>)roomDelegate
                  andPeerFactory:(RTCPeerConnectionFactory *)factory;

///-----------------------------------
/// @name Properties
///-----------------------------------

/// VCXRoomDelegate were this room will invoke methods as events.
@property (weak, nonatomic, readonly) id <VCXRoomDelegate> delegate;

/// VCXRoomStatsDelegate delegate to receive stats.
/// Notice that you should also set *publishingStats* to YES.
@property (weak, nonatomic) id <VCXRoomStatsDelegate> statsDelegate;

/// VCXSignalingChannel signaling delegate instance associtated with this room.
/// Is not required for you to set this property manually.
@property VCXSignalingChannel *signalingChannel;

/// The status of this Room.
@property (nonatomic, readonly) VCXRoomStatus status;

/// Full response after signalling channel connect the server.
@property NSDictionary *roomMetadata;

/// The VCX room id for this room instance.
@property NSString *roomId;

/// NSString stream id of the stream being published
@property (readonly) NSString *publishStreamId;

/// VCXStream referencing the stream being published.
@property (weak, readonly) VCXStream *publishStream;

/// VCXStream streams in the room.
@property (readonly) NSMutableDictionary *streamsByStreamId;

/// List of remote VCXStream streams available in this room.
/// They might be subscribed or not.
@property (readonly) NSArray *remoteStreams;

/// BOOL set/get enable recording of the stream being published.
@property BOOL recordEnabled;

/// BOOL is P2P kind of room.
@property (readonly) BOOL peerToPeerRoom;

/// RTC Factory shared by streams of this room.
@property RTCPeerConnectionFactory *peerFactory;

/// BOOL enable/disable log publishing stats.
/// Stats are collected each 2 seconds max, having this flag on produces
/// console output, take a look to VCXRoomStatsDelegate to being able
/// to receive events when stats are collected.
@property BOOL publishingStats;

/// Represent a dictionary with the default values that will be sent at the
/// moment of subscribe an VCXStream.
@property NSMutableDictionary *defaultSubscribingStreamOptions;

@property (nonatomic) BOOL moderatorHardMuteActiveState;
@property (nonatomic) BOOL participantHardMuteActiveState;

///-----------------------------------
/// @name Public Methods
///-----------------------------------

/**
 Creates a VCXSignalingChannel instance using the given token.
 
 This method is **required** if you have instantiated VCXRoom class without
 provided a token.
 
 @param encodedToken The auth token for room access. See initWithEncodedToken:
 for token composition details.
 
 @see initWithDelegate:
 */
- (void)connectWithEncodedToken:(NSString *)encodedToken;

/**
 Publishes a given VCXStream with given options.
 
 @param stream The stream from where we will be publishing.
 
 @see VCXRoomDelegate:room:didPublishStream:
 */
- (void)publish:(VCXStream *)stream;

/**
 Un-Publish the stream being published.
 */
- (void)unpublish;

/**
 Subscribe to a remote stream.
 
 @param stream VCXStream object containing a valid streamId.
 
 You should be connected to the room before subscribing to a stream.
 To know how to get streams ids take a look at the following methods:
 @see VCXRoomDelegate:room:didAddedStream:
 
 @returns Boolean indicating if started to signaling to subscribe the
 given stream.
 */
- (BOOL)subscribe:(VCXStream *)stream;

/**
 Unsubscribe from a remote stream.
 
 @param stream The stream you want to unsubscribe.
 @see VCXRoomDelegate:room:didUnSubscribeStream:
 */
- (void)unsubscribe:(VCXStream *)stream;

/**
 Leave the room.
 
 RTC and WS connections will be closed.
 */
- (void)disconnect;

//To Forcefully disconnect other users(participant)
-(void)disconnectUsers:(NSArray *)clientIds role:(NSArray *)role;

//to send vcx sdk logs.
-(void)postClientLogs;

//To start Recording
-(void)startRecord;

//To stop Recording
-(void)stopRecord;

//- (void)stopAudio;
//- (void)startAudio;

#pragma mark - CC
- (void)FloorRequest;
- (void)ProcessFloorRequest:(NSString *)clientId : (NSString *)status;

#pragma mark-
/**
 mute all audio stream.
 
 Note: Hardmute functionality is only applicable to moderator.
 
 @see VCXRoomDelegate:didMutedAllUser::data:
 
 */
- (void)muteAllUser;

/**
 unmute all audio stream.
 
 Note: Hardmute functionality is only applicable to moderator.
 
 @see VCXRoomDelegate:didUnMutedAllUser:data:
 
 */
- (void)unMuteAllUser;

/**
 mute single audio stream.
 
 Note: Hardmute functionality is only applicable to moderator.
 
 @param clientId is the participant who is being mute to the floor.
 
 @see VCXRoomDelegate:didMutedSingleUser:::data:
 
 */

- (void)muteSingleUser:(NSString*)clientId;

/**
 unmute single audio stream.
 
 Note: Hardmute functionality is only applicable to moderator.
 
 @param clientId is the participant who is being mute to the floor.
 
 @see VCXRoomDelegate:didUnMutedSingleUser:::data:
 
 */

- (void)unMuteSingleUser:(NSString*)clientId;


-(VCXStream *)initlocalStream:(NSDictionary *)publishStreamInfo;
@end

