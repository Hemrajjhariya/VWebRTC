#import <Foundation/Foundation.h>
@import WebRTC;

#import "VCXRTCLib.h"
#import "VCXRoom.h"
#import "VCXStream.h"
#import "VCXPlayerView.h"

@protocol VCXRTCLibDelegate <NSObject>
@optional

@end


@interface VCXRTCLib : NSObject<VCXRoomDelegate>{
    
}
/// VCXRTCLibDelegate will invoke methods as events.
@property (strong, nonatomic, readonly) id <VCXRTCLibDelegate> delegate;


/**
 
 To quick start and join the room.
 
 @param token: it is encoded token string received from VCX application server.
 @param (id <VCXRTCLibDelegate>). If developer looks to handle the success or failure of the action, then they can implement delegates methods for the same.
 @param Local-Stream-Info: JSON. Refer Appendix: Local-Stream-Info JSON
 
 @return VCXRoom object
 */

-(VCXStream *)joinRoom:(NSString *)token delegate:(id)delegate PublishStreamInfo:(NSDictionary *)publishStreamInfo;
@end

