#import <UIKit/UIKit.h>
@import WebRTC;
#import "VCXStream.h"

@interface VCXPlayerView : UIView <RTCEAGLVideoViewDelegate>

///-----------------------------------
/// @name Initializers
///-----------------------------------

/**
 Create a Player View with a given stream that is being
 consumed.
 
 @param liveStream The stream that is being consumed by the client.
 
 For example you can initialize a player right after VCXRoomDelegate
 has fired VCXRoomDelegate:didSubscribeStream passing the VCXStream
 object to this initializer.
 
 @see VCXRoomDelegate
 
 @returns instancetype
 */
- (instancetype)initWithLiveStream:(VCXStream *)liveStream;

/**
 Create a Player View with the given stream that is being consumed in
 a custom frame.
 
 @param liveStream The stream that is being consumed by the client.
 @param frame Custom frame where this control should be rendered.

 @see VCXRoomDelegate
 
 @returns instancetype
 */
- (instancetype)initWithLiveStream:(VCXStream *)liveStream frame:(CGRect)frame;


/**
 Remove the current assigned rendered for this player
 */
- (void)removeRenderer;

//to add stream in player view.
-(VCXPlayerView *)addStream:(VCXStream *)liveStream player:(VCXPlayerView *)player;

///-----------------------------------
/// @name Properties
///-----------------------------------

/// Stream object that contains a media stream
@property (strong, nonatomic) VCXStream *stream;

/// View where the video gets rendered
@property (strong, nonatomic, readonly) RTCEAGLVideoView *videoView;

@end
