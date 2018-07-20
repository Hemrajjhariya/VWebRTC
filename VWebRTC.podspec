
Pod::Spec.new do |s|
s.name              = 'VWebRTC'
s.version           = '1.0'
s.summary           = 'A really cool SDK that logs stuff.'
s.homepage          = 'https://github.com/Hemrajjhariya/VWebRTC'

s.author            = { 'Hemraj' => 'hemrajjhariya@mail.com' }
s.license           = { :type => 'Apache-2.0', :file => 'LICENSE' }

s.platform          = :ios
s.source            = { :http => 'https://github.com/Hemrajjhariya/NewSDK/archive/5.0.zip' }

s.ios.deployment_target = '9.0'
s.ios.vendored_frameworks = 'NewSDK-5.0/NewSDK/WebRTC.framework'
s.ios.vendored_frameworks = 'VCXiOS.framework'
s.ios.dependency 'SVProgressHUD'
s.ios.dependency 'Socket.IO-Client-Swift'


end



