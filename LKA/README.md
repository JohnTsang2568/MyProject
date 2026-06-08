# LKA — Lane Keeping Assistant

A traditional computer vision prototype for lane detection and lane keeping.

## Features

- **Lane Detection**: Threshold binarization and Canny edge detection
- **Lane Offset Calculation**: Computes pixel offset between lane center and image center within the ROI
- **PID Steering Control**: Converts offset to steering angle for lane keeping simulation
- **Visualization**: ROI bounding box, lane centerline, and steering arrow overlay
- **Video Processing**: Frame-by-frame real-time processing from video files

## Dependencies

```
numpy
opencv-python
matplotlib
```

Install:

```bash
pip install -r requirements.txt
```

## Usage

```bash
python LineKeepingAssistant.py
```

The script processes all PNG images under `test_images/`, displays results, then attempts to read `test_video.mp4` for video processing.

## Project Structure

```
LKA/
├── LineKeepingAssistant.py   # Main script
├── test_images/              # Test images
├── requirements.txt          # Python dependencies
└── README.md
```

## Pipeline

1. Read image → grayscale
2. Binarize to extract white lane pixels
3. Use bottom 33% as ROI
4. Compute offset between lane pixel center and image center
5. PID controller converts offset to steering angle
6. Overlay visualization on original image
