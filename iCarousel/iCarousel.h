//
//  iCarousel.h
//
//  Created by Nick Lockwood on 01/04/2011.
//  Copyright 2010 Charcoal Design. All rights reserved.
//
//  Get the latest version of iCarousel from either of these locations:
//
//  http://charcoaldesign.co.uk/source/cocoa#icarousel
//  https://github.com/demosthenese/icarousel
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source distribution.


#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

typedef UIView View;

#else

#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>

typedef NSView View;

#endif


typedef enum
{
    iCarouselTypeLinear = 0,
    iCarouselTypeRotary,
    iCarouselTypeInvertedRotary,
    iCarouselTypeCylinder,
    iCarouselTypeInvertedCylinder,
    iCarouselTypeCoverFlow,
    iCarouselTypeCustom
}
iCarouselType;


@protocol iCarouselDataSource, iCarouselDelegate;

@interface iCarousel : View
#ifdef __i386__
{
    id<iCarouselDelegate> delegate;
    id<iCarouselDataSource> dataSource;
    iCarouselType type;
    float perspective;
    NSInteger numberOfItems;
    NSInteger numberOfPlaceholders;
    View* contentView;
    NSArray* itemViews;
    NSArray* placeholderViews;
    NSInteger previousItemIndex;
    float itemWidth;
    float scrollOffset;
    float currentVelocity;
    NSTimer* timer;
    NSTimeInterval previousTime;
    BOOL decelerating;
    BOOL scrollEnabled;
    float decelerationRate;
    BOOL bounces;
    CGSize contentOffset;
    CGSize viewpointOffset;
    float startOffset;
    float endOffset;
    NSTimeInterval scrollDuration;
    NSTimeInterval startTime;
    BOOL scrolling;
    float previousTranslation;
	BOOL centerItemWhenSelected;
	BOOL shouldWrap;
}
#endif

@property (nonatomic, assign) IBOutlet id<iCarouselDataSource> dataSource;
@property (nonatomic, assign) IBOutlet id<iCarouselDelegate> delegate;
@property (nonatomic, assign) iCarouselType type;
@property (nonatomic, assign) float perspective;
@property (nonatomic, assign) float decelerationRate;
@property (nonatomic, assign) BOOL scrollEnabled;
@property (nonatomic, assign) BOOL bounces;
@property (nonatomic, assign) CGSize contentOffset;
@property (nonatomic, assign) CGSize viewpointOffset;
@property (nonatomic, readonly) NSInteger numberOfItems;
@property (nonatomic, readonly) NSInteger numberOfPlaceholders;
@property (nonatomic, readonly) NSInteger currentItemIndex;
@property (nonatomic, retain, readonly) NSArray *itemViews;
@property (nonatomic, retain, readonly) NSArray *placeholderViews;
@property (nonatomic, readonly) float itemWidth;
@property (nonatomic, retain, readonly) View *contentView;

- (void)scrollByNumberOfItems:(NSInteger)itemCount duration:(NSTimeInterval)duration;
- (void)scrollToItemAtIndex:(NSInteger)index duration:(NSTimeInterval)duration;
- (void)scrollToItemAtIndex:(NSInteger)index animated:(BOOL)animated;
- (void)reloadData;

#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED

@property (nonatomic, assign) BOOL centerItemWhenSelected;

- (void)removeItemAtIndex:(NSInteger)index animated:(BOOL)animated;
- (void)insertItemAtIndex:(NSInteger)index animated:(BOOL)animated;

#endif

@end


@protocol iCarouselDataSource <NSObject>

- (NSUInteger)numberOfItemsInCarousel:(iCarousel *)carousel;
- (View *)carousel:(iCarousel *)carousel viewForItemAtIndex:(NSUInteger)index;

@optional

- (NSUInteger)numberOfPlaceholdersInCarousel:(iCarousel *)carousel;
- (View *)carousel:(iCarousel *)carousel placeholderViewAtIndex:(NSUInteger)index;

@end


@protocol iCarouselDelegate <NSObject>

@optional

- (void)carouselDidScroll:(iCarousel *)carousel;
- (void)carouselCurrentItemIndexUpdated:(iCarousel *)carousel;
- (float)carouselItemWidth:(iCarousel *)carousel;
- (BOOL)carouselShouldWrap:(iCarousel *)carousel;
- (CATransform3D)carousel:(iCarousel *)carousel transformForItemView:(View *)view withOffset:(float)offset;

#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED

- (void)carousel:(iCarousel *)carousel didSelectItemAtIndex:(NSInteger)index;

#endif

@end