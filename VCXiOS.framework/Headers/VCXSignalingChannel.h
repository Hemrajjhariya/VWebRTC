@import WebRTC;

#import "VCXSignalingMessage.h"
#import "VCXSignalingEvent.h"

#import "VCXClientDelegate.h"

@class VCXSignalingChannel;

///-----------------------------------
/// @protocol VCXSignalingChannelDelegate
///-----------------------------------

@protocol VCXSignalingChannelDelegate <NSObject>

@property NSString *streamId;
@property NSString *peerSocketId;

/**
 Event fired when VCX server has validated our token.
 
 @param signalingChannel VCXSignalingChannel the channel that emit the message.
 */
- (void)signalingChannelDidOpenChannel:(VCXSignalingChannel *)signalingChannel;

/**
 Event fired each time VCXSignalingChannel has received a new VCXSignalingMessage.
 
 @param channel VCXSignalingChannel the channel that emit the message.
 @param message VCXSignalingMessage received by channel.
 */
- (void)signalingChannel:(VCXSignalingChannel *)channel didReceiveMessage:(VCXSignalingMessage *)message;

/**
 Event fired when VCX is ready to receive a publishing stream.

 @param signalingChannel VCXSignalingChannel the channel that emit the message.
 @param peerSocketId Id of the socket in a p2p publishing without MCU. Pass nil if
        you are not setting a P2P room.
 */
- (void)signalingChannel:(VCXSignalingChannel *)signalingChannel
  readyToPublishStreamId:(NSString *)streamId
            peerSocketId:(NSString *)peerSocketId;

/**
 Event fired when VCX failed to publishing stream.
 
 @param signalingChannel VCXSignalingChannel the channel that emit the message.
 */
- (void)signalingChannelPublishFailed:(VCXSignalingChannel *)signalingChannel;

/**
 Event fired each time VCXSignalingChannel has received a confirmation from the server
 to subscribe a stream.
 This event is fired to let Client know that it can start signaling to subscribe the stream.
 
 @param channel VCXSignalingChannel the channel that emit the message.
 @param streamId Id of the stream that will be subscribed.
 @param peerSocketId pass nil if is MCU being used.
 */
- (void)signalingChannel:(VCXSignalingChannel *)channel
readyToSubscribeStreamId:(NSString *)streamId
            peerSocketId:(NSString *)peerSocketId;

@end

///-----------------------------------
/// @protocol VCXSignalingChannelRoomDelegate
///-----------------------------------

@protocol VCXSignalingChannelRoomDelegate <NSObject>

/**
 This event is fired when a token was not successfuly used.
 
 @param channel VCXSignalingChannel the channel that emit the message.
 @param reason String of error returned by the server.
 */
- (void)signalingChannel:(VCXSignalingChannel *)channel didError:(NSString *)reason;
- (void)signalingChannel:(VCXSignalingChannel *)channel didRecoonect:(NSString *)reason;

/**
 Event fired as soon a client connect to a room.

 @param channel VCXSignalingChannel the channel that emit the message.
 @param roomMeta Metadata associated to the room that the client just connect.
 */
- (void)signalingChannel:(VCXSignalingChannel *)channel didConnectToRoom:(NSDictionary *)roomMeta;

/**
 Event fired as soon as rtc channels were disconnected and websocket
 connection is about to be closed.
 
 @param channel VCXSignalingChannel the channel that emit the message.
 @param roomMeta Metadata associated to the room that the client just connect.
 */
- (void)signalingChannel:(VCXSignalingChannel *)channel didDisconnectOfRoom:(NSDictionary *)roomMeta;

/**
 Event fired when a new stream id has been created and server is ready
 to start publishing it.
 
 @param channel VCXSignalingChannel the channel that emit the message.
 @param streamId NSString id of the stream that will be published.
 */
- (void)signalingChannel:(VCXSignalingChannel *)channel didReceiveStreamIdReadyToPublish:(NSString *)streamId;

/**
 Event fired when a recording of a stream has started.
 
 @param channel VCXSignalingChannel the channel that emit the message.
 @param streamId NSString id of the stream being recorded.
 @param recordingId NSString id of the recording id on VCX server.
 @param recordingDate NSDate when the server start to recording the stream.
 */
- (void)signalingChannel:(VCXSignalingChannel *)channel didStartRecordingStreamId:(NSString *)streamId
                                                                 withRecordingId:(NSString *)recordingId
                                                                       recordingDate:(NSDate *)recordingDate;
/**
 Event fired when a recording of a stream has failed.
 
 @param channel VCXSignalingChannel the channel that emit the message.
 @param streamId NSString id of the stream being recorded.
 @param errorMsg Error string sent from the server.
 */
- (void)signalingChannel:(VCXSignalingChannel *)channel didFailStartRecordingStreamId:(NSString *)streamId
            withErrorMsg:(NSString *)errorMsg;


//delegate method when recording start successful
-(void)signalingRecordingDidStart:(NSArray *)response;

//when recording fails.
//-(void)signalingRecordingDidFail:(NSString *)response;

//delegate method when recording stop successful
-(void)signalingRecordingDidStop:(NSArray *)response;

//when recording stop fails.
//-(void)signalingRecordingDidStopFail:(NSString *)response;

/**
 Event fired when a new StreamId has been added to a room.
 
 @param channel VCXSignalingChannel the channel that emit the message.
 @param streamId NSString added to the room.
 @param event Event name and data carried
 */
- (void)signalingChannel:(VCXSignalingChannel *)channel
    didStreamAddedWithId:(NSString *)streamId
                   event:(VCXSignalingEvent *)event;

/**
 Event fired when a StreamId has been removed from a room, not necessary this
 stream has been consumed.
 
 @param channel VCXSignalingChannel the channel that emit the message.
 @param streamId NSString of the removed stream.
 */
- (void)signalingChannel:(VCXSignalingChannel *)channel didRemovedStreamId:(NSString *)streamId;

/**
 Event fired when a StreamId previously subscribed has been unsubscribed.
 
 @param channel VCXSignalingChannel the channel that emit the message.
 @param streamId NSString of the unsubscribed stream.
 */
- (void)signalingChannel:(VCXSignalingChannel *)channel didUnsubscribeStreamWithId:(NSString *)streamId;

/**
 Event fired when a published stream is being unpublished.

 @param channel VCXSignalingChannel the channel that emit the message.
 @param streamId NSString of the stream being unpublished
 */
- (void)signalingChannel:(VCXSignalingChannel *)channel didUnpublishStreamWithId:(NSString *)streamId;

/**
 Event fired when some peer request to subscribe to a given stream.

 @param channel VCXSignalingChannel the channel that emit the message.
 @param streamId NSString of the unsubscribed stream.
 @param peerSocketId String that identifies the peer connection for the stream.

 */
- (void)signalingChannel:(VCXSignalingChannel *)channel didRequestPublishP2PStreamWithId:(NSString *)streamId
                                                                        peerSocketId:(NSString *)peerSocketId;

/**
 Method called when the signaling channels needs a new client to operate a connection.

 @param channel VCXSignalingChannel the channel that emit the message.

 @returns VCXClientDelegate instance.
 */
- (id<VCXSignalingChannelDelegate>)clientDelegateRequiredForSignalingChannel:(VCXSignalingChannel *)channel;

/**
 Event fired when data stream received.
 
 @param channel VCXSignalingChannel the channel that emit the message.
 @param streamId NSString id of the stream received from.
 @param dataStream NSDictionary having message and timestamp.
 */
- (void)signalingChannel:(VCXSignalingChannel *)channel
            fromStreamId:(NSString *)streamId
	  receivedDataStream:(NSDictionary *)dataStream;

/**
 Event fired when data stream received.
 
 @param channel VCXSignalingChannel the channel that emit the message.
 @param streamId NSString id of the stream received from.
 @param dataStream NSDictionary having message and timestamp.
 */
- (void)signalingChannel:(VCXSignalingChannel *)channel
            fromStreamId:(NSString *)streamId
      didBandWidthAlert:(NSArray *)dataStream;


/**
 Event fired when stream atrribute updated.
 
 @param channel VCXSignalingChannel the channel that emit the message.
 @param streamId NSString id of the stream received from.
 @param attributes NSDictionary having custom attribute.
 */
- (void)signalingChannel:(VCXSignalingChannel *)channel
            fromStreamId:(NSString *)streamId
   updateStreamAttributes:(NSDictionary *)attributes;

//on Logs scuccess upload
-(void)signalingLogsSuccess:(NSString *)message;
//on Logs Failure upload
-(void)signalingLogsFailure:(NSString *)message;

#pragma mark - ChairControl
//P
- (void)signalingChannel:(VCXSignalingChannel *)channel didReciveFloorRequest:(NSArray *)Data;
- (void)signalingChannel:(VCXSignalingChannel *)channel didReciveFloorGranted:(NSArray *)Data;
- (void)signalingChannel:(VCXSignalingChannel *)channel didFloorReleased:(NSArray *)Data;
- (void)signalingChannel:(VCXSignalingChannel *)channel didFloorDeny:(NSArray *)Data;
//M
- (void)signalingChannel:(VCXSignalingChannel *)channel didFloorRequested:(NSArray *)Data;
- (void)signalingChannel:(VCXSignalingChannel *)channel didProcessFloorRequest:(NSArray *)Data;
//- (void)signalingChannel:(VCXSignalingChannel *)channel didResponceReleaseFloor:(NSArray *)Data;

//H
- (void)signalingChannel:(VCXSignalingChannel *)channel didResponceMuteAllUser:(NSArray *)Data;
- (void)signalingChannel:(VCXSignalingChannel *)channel didResponceUnMuteAllUser:(NSArray *)Data;
- (void)signalingChannel:(VCXSignalingChannel *)channel didResponceMuteSingleUser:(NSArray *)Data;
- (void)signalingChannel:(VCXSignalingChannel *)channel didResponceUnMuteSingleUser:(NSArray *)Data;

//lisner

- (void)signalingChannel:(VCXSignalingChannel *)channel recievedMuteAll:(NSArray *)Data;
- (void)signalingChannel:(VCXSignalingChannel *)channel recievedMuteUser:(NSArray *)Data;

//
-(void)signalingChannel:(VCXSignalingChannel *)channel userDidJoined:(NSArray *)Data;
-(void)signalingChannel:(VCXSignalingChannel *)channel userDidDisconnected:(NSArray *)Data;

   #pragma mark- recording Participant
-(void)signalingChannel:(VCXSignalingChannel *)channel roomRecordOn:(NSArray *)Data;
-(void)signalingChannel:(VCXSignalingChannel *)channel roomRecordOff:(NSArray *)Data;


@end

/**
 @interface VCXSignalingChannel
 
 */
@interface VCXSignalingChannel : NSObject

///-----------------------------------
/// @name Initializers
///-----------------------------------

/**
 Creates an instance of VCXSignalingChannel.
 
 @param token The encoded token to access a room.
 @param roomDelegate VCXSignalingChannelRoomDelegate instance that will receive
        events related to stream addition, recording started, etc.
 
 @return instancetype
 */
- (instancetype)initWithEncodedToken:(NSString *)token
                        roomDelegate:(id<VCXSignalingChannelRoomDelegate>)roomDelegate
                      clientDelegate:(id<VCXClientDelegate>)clientDelegate;

///-----------------------------------
/// @name Properties
///-----------------------------------

/// VCXSignalingChannelRoomDelegate reference
@property (weak, nonatomic) id<VCXSignalingChannelRoomDelegate> roomDelegate;


///-----------------------------------
/// @name Public Methods
///-----------------------------------

- (void)connect;
- (void)disconnect;
- (void)enqueueSignalingMessage:(VCXSignalingMessage *)message;
- (void)sendSignalingMessage:(VCXSignalingMessage *)message;
- (void)drainMessageQueueForStreamId:(NSString *)streamId
                        peerSocketId:(NSString *)peerSocketId;
- (void)publish:(NSDictionary *)options
            signalingChannelDelegate:(id<VCXSignalingChannelDelegate>)delegate;
- (void)unpublish:(NSString *)streamId
            signalingChannelDelegate:(id<VCXSignalingChannelDelegate>)delegate;
- (void)publishToPeerID:(NSString *)peerSocketId
            signalingChannelDelegate:(id<VCXSignalingChannelDelegate>)delegate;
- (void)subscribe:(NSString *)streamId
    streamOptions:(NSDictionary *)streamOptions
signalingChannelDelegate:(id<VCXSignalingChannelDelegate>)delegate;
- (void)unsubscribe:(NSString *)streamId;
- (void)startRecording:(NSString *)streamId;
- (void)stopRecording:(NSString *)streamId;
    
- (void)sendDataStream:(VCXSignalingMessage *)message;
- (void)updateStreamAttributes:(VCXSignalingMessage *)message;
-(void)sendLogsToServer:(NSString *)logId logText:(NSString *)logText;

#pragma mark- CC
- (void)RequestFlloor;
- (void)ProcessFloorRequest:(NSString *)clientId : (NSString *)status;
- (void)ReleaseFloor:(NSDictionary *)Action;

#pragma mark-
- (void)muteAllUser;
- (void)unMuteAllUser;
- (void)muteSingleUser:(NSString*)clientId;
- (void)unMuteSingleUser:(NSString*)clientId;
@end
