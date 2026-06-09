# OpenCV Image Resizing Application
A simple C++ application built with OpenCV that demonstrates two image resizing algorithms:
- Nearest Neighbor Interpolation
- Bilinear Interpolation

The application allows users to:
- Open and display images
- Zoom images
- Shrink images
- Compare interpolation methods visually

## Features

### Nearest Neighbor Interpolation
- Fast resizing method
- Chooses the closest pixel from the source image
- Produces a pixelated effect when zooming

### Bilinear Interpolation
- Uses weighted averages of neighboring pixels
- Produces smoother results
- Better image quality during scaling

## Technologies Used
- C++
- OpenCV

## Project Structure

- `resizeNearest()`  
  Implements nearest neighbor interpolation.
- `resizeBilinear()`  
  Implements bilinear interpolation.
- `testZoomShrink()`  
  Loads an image and applies scaling.
- `main()`  
  Console menu for interacting with the application.

## How It Works

1. Open an image
2. Enter a scale factor:
   - `> 1` for zoom
   - `< 1` for shrink
3. The application displays:
   - Original image
   - Nearest Neighbor result
   - Bilinear Interpolation result

## Example
Scale factor:
```txt
2.0
