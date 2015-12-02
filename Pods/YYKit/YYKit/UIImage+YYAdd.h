//
//  UIImage+YYAdd.h
//  YYKit
//
//  Created by ibireme on 13-4-4.
//  Copyright (c) 2013 ibireme. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 Provide some commen method for `UIImage`.
 Image process is based on CoreGraphic and vImage.
 */
@interface UIImage (YYAdd)


#pragma mark - Image Decode
///=============================================================================
/// @name Image Decode
///=============================================================================

/**
 Decompress this image, so when the image is displayed on screen, the main 
 thread won't be blocked by additional decode. It will cost more memory. 
 If the image is already decoded, or fail to decode, it just return itself.
 
 @return a image decoded, or just return itself if no needed.
 
 @see isImageDecoded
 */
- (UIImage *)imageByDecoded;

/**
 Wherher the image can be display on screen without additional decode.
 
 @see imageByDecoded
 
 @warning It just a hint for your code, change it has no other effect.
 */
@property (nonatomic, assign) BOOL isImageDecoded;


#pragma mark - Create image
///=============================================================================
/// @name Create image
///=============================================================================

/**
 Create an animated image with GIF data. After created, you can access
 the images via property '.images'. If the data is not animated gif, this
 function is same as [UIImage imageWithData:data scale:scale];
 
 @discussion     It has a better display performance, but costs more memory
                 (width * height * frames). It only suited to display small gif
                 such as animated emoji. If you want to display large gif, see
                 `YYGIFImage`.
 
 @param data     GIF data.
 
 @param scale    The scale factor
 
 @return A new image created from GIF, or nil when an error occurs.
 */
+ (UIImage *)imageWithSmallGIFData:(NSData *)data scale:(CGFloat)scale;

/**
 Whether the data is animated GIF.
 
 @param data Image data
 
 @return Returns YES only if the data is gif and contains more than one frame,
         otherwise returns NO.
 */
+ (BOOL)isAnimatedGIFData:(NSData *)data;

/**
 Create an image from a PDF file data or path.
 
 @discussion If the PDF has multi page, is just return's the first page's 
 content. Image's scale is equal to current screen's scale, size is same as 
 PDF's origin size.
 
 @param dataOrPath PDF data in `NSData`, or PDF file path in `NSString`.
 
 @return A new image create from PDF, or nil when an error occurs.
 */
+ (UIImage *)imageWithPDF:(id)dataOrPath;

/**
 Create an image from a PDF file data or path.
 
 @discussion If the PDF has multi page, is just return's the first page's
 content. Image's scale is equal to current screen's scale.
 
 @param dataOrPath  PDF data in `NSData`, or PDF file path in `NSString`.
 
 @param size     The new image's size, PDF's content will be stretched as needed.
 
 @return A new image create from PDF, or nil when an error occurs.
 */
+ (UIImage *)imageWithPDF:(id)dataOrPath size:(CGSize)size;

/**
 Create a square image from apple emoji.
 
 @discussion It creates a square image from apple emoji, image's scale is equal
 to current screen's scale. The original emoji image in `AppleColorEmoji` font 
 is in size 160*160 px.
 
 @param emoji single emoji, such as @"😄".
 
 @param size  image's size.
 
 @return Image from emoji, or nil when an error occurs.
 */
+ (UIImage *)imageWithEmoji:(NSString *)emoji size:(CGFloat)size;

/**
 Create and return a 1x1 point size image with the given color.
 
 @param color  The color.
 */
+ (UIImage *)imageWithColor:(UIColor *)color;

/**
 Create and return a pure color image with the given color and size.
 
 @param color  The color.
 @param size   New image's type.
 */
+ (UIImage *)imageWithColor:(UIColor *)color size:(CGSize)size;


#pragma mark - Image Info
///=============================================================================
/// @name Image Info
///=============================================================================

/**
 Returns the color from the pixel pointed in this image.
 
 @param point  The point inside this image.
               point.x is in range [0,image.width-1],
               point.y is in range [0,image.height-1].
               If the point is out of this image, nil value will be returned.
 */
- (UIColor *)colorAtPoint:(CGPoint)point;

/**
 Whether this image has alpha channel.
 */
- (BOOL)hasAlphaChannel;


#pragma mark - Modify Image
///=============================================================================
/// @name Modify Image
///=============================================================================

/**
 Draws the entire image in the specified rectangle, content changed with
 the contentMode.
 
 @discussion This method draws the entire image in the current graphics context, 
 respecting the image's orientation setting. In the default coordinate system, 
 images are situated down and to the right of the origin of the specified 
 rectangle. This method respects any transforms applied to the current graphics 
 context, however.
 
 @param rect        The rectangle in which to draw the image.
 
 @param contentMode Draw content mode
 */
- (void)drawInRect:(CGRect)rect withContentMode:(UIViewContentMode)contentMode;

/**
 Returns a new image which is scaled from this image.
 The image will be stretched as needed.
 
 @param size  The new size to be scaled, values should be positive.
 
 @return      The new image with the given size.
 */
- (UIImage *)imageByResizeToSize:(CGSize)size;

/**
 Returns a new image which is scaled from this image.
 The image content will be changed with thencontentMode.
 
 @param size        The new size to be scaled, values should be positive.
 
 @param contentMode The content mode for image content.
 
 @return The new image with the given size.
 */
- (UIImage *)imageByResizeToSize:(CGSize)size contentMode:(UIViewContentMode)contentMode;

/**
 Returns a new image which is cropped from this image.
 
 @param rect  Image's inner rect.
 
 @return      The new image, or nil if an error occurs.
 */
- (UIImage *)imageByCropToRect:(CGRect)rect;

/**
 Returns a new image which is edge inset from this image.
 
 @param insets  Inset (positive) for each of the edges, values can be negative to 'outset'.
 
 @param color   Extend edge's fill color, nil means clear color.
 
 @return        The new image, or nil if an error occurs.
 */
- (UIImage *)imageByInsetEdge:(UIEdgeInsets)insets withColor:(UIColor *)color;

/**
 Rounds the image with a given corner size.
 
 @param radius  The radius of each corner oval. Values larger than half the
                rectangle's width or height are clamped appropriately to half
                the width or height.
 */
- (UIImage *)imageByRoundCornerRadius:(CGFloat)radius;

/**
 Rounds the image with a given corner size.
 
 @param radius       The radius of each corner oval. Values larger than half the
                     rectangle's width or height are clamped appropriately to
                     half the width or height.
 
 @param corners      A bitmask value that identifies the corners that you want
                     rounded. You can use this parameter to round only a subset
                     of the corners of the rectangle.
 
 @param borderWidth  The inset border with clear color. Values larger than half
                     the rectangle's width or height are clamped appropriately
                     to half the width or height.
 */
- (UIImage *)imageByRoundCornerRadius:(CGFloat)radius
                              corners:(UIRectCorner)corners
                          borderWidth:(CGFloat)borderWidth;

/**
 Returns a rotated image (relative to the center).
 
 @param radians   Rotated radians in counterclockwise.⟲
 
 @param fitSize   YES: new image's size is extend to fit all content.
                  NO: image's size will not change, content may be clipped.
 */
- (UIImage *)imageByRotate:(CGFloat)radians fitSize:(BOOL)fitSize;

/**
 Returns a image rotated counterclockwise by a quarter‑turn (90°). ⤺
 The width and height will be exchanged.
 */
- (UIImage *)imageByRotateLeft90;

/**
 Returns a image rotated clockwise by a quarter‑turn (90°). ⤼
 The width and height will be exchanged.
 */
- (UIImage *)imageByRotateRight90;

/**
 Returns a image rotated 180° . ↻
 */
- (UIImage *)imageByRotate180;

/**
 Returns a vertically flipped image. ⥯
 */
- (UIImage *)imageByFlipVertical;

/**
 Returns a horizontally flipped image. ⇋
 */
- (UIImage *)imageByFlipHorizontal;


#pragma mark - Image Effect
///=============================================================================
/// @name Image Effect
///=============================================================================

/**
 Tint the image in alpha channel with the given color.
 
 @param color  The color.
 */
- (UIImage *)imageByTintColor:(UIColor *)color;

/**
 Returns a grayscaled image.
 */
- (UIImage *)imageByGrayscale;

/**
 Applies a blur effect to this image. Suitable for blur any content.
 */
- (UIImage *)imageByBlurSoft;

/**
 Applies a blur effect to this image. Suitable for blur any content except pure white.
 */
- (UIImage *)imageByBlurLight;

/**
 Applies a blur effect to this image. Suitable for displaying black text.
 */
- (UIImage *)imageByBlurExtraLight;

/**
 Applies a blur effect to this image. Suitable for displaying white text.
 */
- (UIImage *)imageByBlurDark;

/**
 Applies a blur and tint color to this image.
 
 @param tintColor  The tint color.
 */
- (UIImage *)imageByBlurWithTint:(UIColor *)tintColor;

/**
 Applies a blur, tint color, and saturation adjustment to this image,
 optionally within the area specified by @a maskImage.
 
 @param blurRadius     The radius of the blur in points, 0 means no blur effect.
 
 @param tintColor      An optional UIColor object that is uniformly blended with
                       the result of the blur and saturation operations. The
                       alpha channel of this color determines how strong the
                       tint is. nil means no tint.
 
 @param tintBlendMode  The @a tintColor blend mode. Default is kCGBlendModeNormal (0).
 
 @param saturation     A value of 1.0 produces no change in the resulting image.
                       Values less than 1.0 will desaturation the resulting image
                       while values greater than 1.0 will have the opposite effect.
                       0 means gray scale.
 
 @param maskImage      If specified, @a inputImage is only modified in the area(s)
                       defined by this mask.  This must be an image mask or it
                       must meet the requirements of the mask parameter of
                       CGContextClipToMask.
 
 @return               image with effect, or nil if an error occurs (e.g. no
                       enough memory).
 */
- (UIImage *)imageByBlurRadius:(CGFloat)blurRadius
                     tintColor:(UIColor *)tintColor
                      tintMode:(CGBlendMode)tintBlendMode
                    saturation:(CGFloat)saturation
                     maskImage:(UIImage *)maskImage;

@end


#pragma mark - Helper functions

/**
 Create a decoded image (may useful for display), see `-imageByDecoded`.
 */
CGImageRef CGImageCreateDecoded(CGImageRef imageRef);
