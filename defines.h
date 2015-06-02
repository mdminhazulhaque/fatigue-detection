#define VIDEO_MODE
#define SUCCESS 1
#define FAIL   -1

#ifdef VIDEO_MODE
#define EYE_ROI_RADIUS_W 22
#define EYE_ROI_RADIUS_H 18
#define FRAME_WIDTH  720
#define FRAME_HEIGHT 480
#else
#define EYE_ROI_RADIUS_W 13
#define EYE_ROI_RADIUS_H 15
#define FRAME_WIDTH 640
#define FRAME_HEIGH 480
#endif
