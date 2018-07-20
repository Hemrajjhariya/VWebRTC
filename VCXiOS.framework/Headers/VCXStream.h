@import WebRTC;
#import <Foundation/Foundation.h>
#import "VCXLogger.h"
#import "VCXSignalingChannel.h"
#import "VCXSignalingMessage.h"
@class VCXRoom;
@class VCXStream;

static NSString * _Nonnull const kVCXAudioLabel = @"LCMSa0";
static NSString * _Nonnull const kVCXVideoLabel = @"LCMSv0";

/// Video option
static NSString * _Nonnull const kStreamOptionVideo         = @"video";
/// Audio option
static NSString * _Nonnull const kStreamOptionAudio         = @"audio";
/// Data option
static NSString * _Nonnull const kStreamOptionData          = @"data";
/// minVideoBW
static NSString * _Nonnull const kStreamOptionMinVideoBW    = @"minVideoBW";
/// maxVideoBW
static NSString * _Nonnull const kStreamOptionMaxVideoBW    = @"maxVideoBW";
/// scheme
static NSString * _Nonnull const kStreamOptionScheme        = @"scheme";

@protocol VCXStreamDelegate <NSObject>
@optional

/**
 Fired when audio self mute/unmute events call on VCXStream object.
 
 @param data NSDictionary gives the result of Audio event.
 */
-(void)didAudioEvents:(NSDictionary *_Nullable)data;

/**
 Fired when video self On/Off events call on VCXStream object.
 
 @param data NSDictionary gives the result of Video event.
 */

-(void)didVideoEvents:(NSDictionary *_Nullable)data;

/**
 Fired when a data stream is received.
 
 @param stream Instance of the stream where event happen.
 @param data stream message received.
 
 */
- (void)stream:(VCXStream *_Nullable)stream didReceiveData:(NSDictionary *_Nullable)data;

/**
 Fired when a bandWidth alert received from server.
 
 @param stream Instance of the stream where event happen.
 @param data bandWidthAlert info on a stream.
 
 */
- (void)stream:(VCXStream *_Nullable)stream didBandWidthAlert:(NSArray *_Nullable)data;

@end

/**
 @interface VCXStream
 
 Represents a wrapper around an audio/video RTC stream that can be used to
 access local media and publish it in a VCXRoom, or receive video from.
 */
@interface VCXStream: NSObject

///-----------------------------------
/// @name Initializers
///-----------------------------------

/**
 Creates an instace of VCXStream capturing audio/video from the host device
 with given Audio and Video contraints.
 
 Notice that the constraints passed to this initializer will also be set as default
 constraint properties for defaultAudioConstraints and defaultVideoConstraints.
 
 @param videoConstraints RTCMediaConstraints that apply to this stream.
 @param audioConstraints RTCMediaConstraints that apply to this stream.
 
 @see initLocalStream:
 @see initLocalStreamWithOptions:attributes:videoConstraints:audioConstraints:
 
 @return instancetype
 */
- (instancetype _Nonnull)initLocalStreamVideoConstraints:(nullable RTCMediaConstraints *)videoConstraints
                                        audioConstraints:(nullable RTCMediaConstraints *)audioConstraints
                                     ;

/**
 Creates an instace of VCXStream capturing audio/video from the host device
 providing options, attributes and Audio and Video contraints.
 
 Notice that the constraints passed to this initializer will also be set as default
 constraint properties for defaultAudioConstraints and defaultVideoConstraints.
 
 @param options dictionary. @see kStreamOption for options keys.
 @param attributes dictionary. @see setAttributes.
 @param videoConstraints RTCMediaConstraints that apply to this stream.
 @param audioConstraints RTCMediaConstraints that apply to this stream.
 
 @see initLocalStream:
 @see initLocalStreamVideoConstraints:audioConstraints:
 
 @return instancetype
 */
- (instancetype _Nonnull)initLocalStreamWithOptions:(nullable NSDictionary *)options
                                         attributes:(nullable NSDictionary *)attributes
                                   videoConstraints:(nullable RTCMediaConstraints *)videoConstraints
                                   audioConstraints:(nullable RTCMediaConstraints *)audioConstraints;
/**
 Creates an instace of VCXStream capturing audio/video from the host device
 providing options, attributes.
 
 @param options dictionary. @see kStreamOption for options keys.
 @param attributes dictionary. @see setAttributes.
 
 @see initLocalStream:
 @see initLocalStreamVideoConstraints:audioConstraints:
 @see initLocalStreamWithOptions:attributes:videoConstraints:audioConstraints:
 
 @return instancetype
 */
- (instancetype _Nonnull)initLocalStreamWithOptions:(nullable NSDictionary *)options
                                         attributes:(nullable NSDictionary *)attributes
                                   signalingChannel:(VCXSignalingChannel *_Nonnull)signalingChannel;

/**
 Creates an instance of VCXStream capturing audio/video data
 from host device with defaultVideoConstraints and defaultAudioConstraints.
 
 @see initWithLocalStreamVideoConstraints:audioConstraints:
 @see initLocalStreamWithOptions:attributes:videoConstraints:audioConstraints:
 
 @return instancetype
 */
- (instancetype _Nonnull)initLocalStream;

/**
 Creates an instance of VCXStream with a given stream id and signaling channel.
 
 @param streamId VCX stream id for this stream object.
 @param attributes Stream attributes. Attributes will not be sent to the server.
 @param signalingChannel Signaling channel used by VCXRoom that handles the stream.
 
 @return instancetype
 */
- (instancetype _Nonnull)initWithStreamId:(nonnull NSString *)streamId
                               attributes:(nullable NSDictionary *)attributes
                         signalingChannel:(nonnull VCXSignalingChannel *)signalingChannel;

/**
 Attempt to switch between FRONT/REAR camera for the local stream
 being capturated.
 
 @returns NSException.
 */
- (NSException *)switchCamera ;

/**
 Indicates if the media stream has audio tracks.
 
 If you want to know if the stream was initializated requesting
 audio look into streamOptions dictionary.
 
 @returns Boolean value.
 */
- (BOOL)hasAudio;

/**
 Indicates if the media stream has video tracks.
 
 If you want to know if the stream was initializated requesting
 video look into streamOptions dictionary.
 
 @returns Boolean value.
 */
- (BOOL)hasVideo;

/**
 Indicates if the stream has data activated.
 
 @returns Boolean value.
 */
- (BOOL)hasData;


/**
 mute/unmute stream audio.
 
 @param isMuted BOOL to send true to mute or false to unmute.
 @see VCXStreamDelegate:didAudioEvents:data:
 */
- (void)muteSelfAudio:(BOOL)isMuted;

/**
 Unmute Audio tracks for this stream.
 */
//- (NSException *)unmute;


/**
 mute/unmute stream video.
 
 @param isMuted BOOL to send true to mute or false to unmute.
 @see VCXStreamDelegate:didVideoEvents:data:
 */
- (void)muteSelfVideo:(BOOL)isMuted;

/**
// stopvideo */
//- (NSException *)stopvideo:(VCXStream *_Nullable)stream ;
//
///**
// startvideo
// */
//- (NSException *)startvideo:(VCXStream *_Nullable)stream ;

/**
 Generates the video tracks for the stream
 */
- (void)generateVideoTracks;

/**
 Generates the audio tracks for the stream
 */
- (void)generateAudioTracks;

/**
 Get attributes of the stream
 */
- (NSDictionary *_Nonnull)getAttributes;

/**
 Set attributes of the stream
 
 Notice that this method will replace the whole dictionary.
 
 If the stream doesn't belong to a connected room, the attributes
 will be marked as dirty and they will be sent to the server
 once the stream gets a functional signaling channel.
 
 If the stream is a remote stream it will not submit attributes.
 */
- (void)setAttributes:(NSDictionary *_Nonnull)attributes;

/**
 Send data stream on channel
 
 data Dictionary.
 */
- (NSException *)sendData:(NSDictionary *_Nonnull)data;

-(void)getReceivedData:(NSDictionary *_Nullable)data;


-(void)getBandWidthAlert:(NSDictionary *_Nullable)data;

///-----------------------------------
/// @name Properties
///-----------------------------------

/// VCXStreamDelegate were this stream will invoke methods as events.
@property (weak, nonatomic) id <VCXStreamDelegate> delegate;


/// RTCMediaStream object that represent the stream a/v data.
@property RTCMediaStream * _Nullable mediaStream;

/// VCX stream id.
@property NSString * _Nullable streamId;

/// VCX stream attributes for the stream being pubished.
@property (strong, nonatomic, readonly) NSDictionary * _Nonnull streamAttributes;

/// Indicates attributes hasn't been sent to VCX yet.
@property (readonly) BOOL dirtyAttributes;

/// VCX stream options.
@property (strong, nonatomic) NSMutableDictionary * _Nonnull streamOptions;

/// Factory instance used to access local media.
@property (strong, nonatomic) RTCPeerConnectionFactory * _Nonnull peerFactory;

/// VCXSignalingChannel instance assigned by VCXRoom at the moment
@property (weak) VCXSignalingChannel * _Nullable signalingChannel;

/// VCXRoom instance at the moment
@property (weak, nonatomic) VCXRoom * _Nullable room;

/// to indicate about localStream object or not.
@property (readonly) BOOL isLocal;

/// Default video contraints.
@property (readonly) RTCMediaConstraints * _Nullable defaultVideoConstraints;

/// Default audio contraints.
@property (readonly) RTCMediaConstraints * _Nullable defaultAudioConstraints;

//@property (strong,nonatomic) NSDictionary * _Nullable receivedDataDictionary;


@end

