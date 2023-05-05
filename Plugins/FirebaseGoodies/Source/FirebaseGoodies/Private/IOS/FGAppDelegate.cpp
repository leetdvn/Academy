// Copyright (c) 2021 Nineva Studios

#if DYNAMIC_LINKS_IOS

#include "FGAppDelegate.h"
#include "DynamicLinksHelper.h"

#import "FirebaseDynamicLinks/FirebaseDynamicLinks.h"

NS_ASSUME_NONNULL_BEGIN

@implementation IOSAppDelegate(FirebaseGoodies)

- (BOOL)application:(UIApplication*)application continueUserActivity : (NSUserActivity*)userActivity restorationHandler : (void(^)(NSArray<id<UIUserActivityRestoring>> *restorableObjects))restorationHandler {
	NSLog(@"application:continueUserActivity:restorationHandler: URL: %@", [userActivity.webpageURL absoluteString]);
	
	DynamicLinksHelper::WasAppOpenViaAppLink = true;
	DynamicLinksHelper::URL = userActivity.webpageURL;
	
	[[FIRDynamicLinks dynamicLinks] handleUniversalLink:userActivity.webpageURL completion:^(FIRDynamicLink* _Nullable dynamicLink, NSError* _Nullable error) {
		NSLog(@"handleUniversalLink:completion:");
		if (dynamicLink != nil) {
			NSLog(@"Dynamic Link URL: %@", [dynamicLink.url absoluteString]);
			DynamicLinksHelper::DynamicLink = (FIRDynamicLink*)CFBridgingRetain(dynamicLink);
		}

		if (error != nil) {
			NSLog(@"Dynamic Link parse error: %@", error.localizedDescription);
		}
	}];

	return true;
}

- (BOOL)application:(UIApplication*)app openURL:(NSURL*)url option:(NSDictionary<UIApplicationOpenURLOptionsKey, id>*)options {
	NSLog(@"application:openURL:option: URL: %@", [url absoluteString]);

	return[self application:app openURL:url sourceApplication:options[UIApplicationOpenURLOptionsSourceApplicationKey] annotation:options[UIApplicationOpenURLOptionsAnnotationKey]];
}

- (BOOL)application:(UIApplication*)application openURL:(NSURL*)url sourceApplication:(nullable NSString*)sourceApplication annotation:(id)annotation {
	NSLog(@"application:openURL:sourceApplication:annotation: URL: %@", [url absoluteString]);
	
	DynamicLinksHelper::WasAppOpenViaUrl = true;
	DynamicLinksHelper::URL = url;
	
	FIRDynamicLink* link = [[FIRDynamicLinks dynamicLinks] dynamicLinkFromCustomSchemeURL:url];
	if (link != nil)
		DynamicLinksHelper::DynamicLink = (FIRDynamicLink*)CFBridgingRetain(link);

	return true;
}

@end

NS_ASSUME_NONNULL_END

#endif
