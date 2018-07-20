#import <Foundation/Foundation.h>

/**
 @interface RTC_Client
 
 This is a dummy class with the purpose of initialize the library
 before being used.
 
 You should call sharedInstance: before any call to other RTC_Client
 classes and methods.
 
 */
@interface VCXRTC : NSObject

/**
 Create a shared instance of RTC_Client.
 
 This initalizer should be called **allways** before start
 using the library.
 
 */
+ (instancetype)sharedInstance;

@end
