import glob
import numpy as np
import cv2
import matplotlib.pyplot as plt
import os

class PIDController:
    def __init__(self, kp=0.02, kd=0.01, ki=0.0):
        self.kp = kp
        self.kd = kd
        self.ki = ki
        self.prev_error = 0
        self.integral = 0

    def compute(self, error, dt=1.0):
        self.integral += error * dt #integral term: sigma(error * dt)
        derivative = (error - self.prev_error) / dt #derivative term: (error - prev_error) / dt
        output = self.kp * error + self.ki * self.integral + self.kd * derivative 
        self.prev_error = error
        # restrict output to a reasonable range (e.g., -30 to 30 degrees)
        return max(-30.0, min(30.0, output))

def draw_arrow(image, angle_deg, position=None):
    h, w = image.shape[0:2]
    if position is None:
        pos = (w // 2, int(h * 0.1))  #top center
    else:
        pos = position
    # arrow length
    length = 50
    # degree to radians
    rad = np.radians(angle_deg)
    end_x = int(pos[0] + length * np.sin(rad))
    end_y = int(pos[1] - length * np.cos(rad))
    # draw arrowed line
    cv2.arrowedLine(image, pos, (end_x, end_y), (0, 0, 255), 3, tipLength=0.3)

def process_pipeline(image_rgb, method='threshold', roi_ratio=0.33, pid=None,dt=1.0):
    # binarize lane
    binary = binarize_lane(image_rgb, method=method)
    # calculate lane offset
    offset = calculate_lane_offset(binary, roi_ratio)
    # PID control to get steering angle
    if pid is not None and offset is not None:
        angle = pid.compute(offset,dt=dt)
    else:
        angle = 0.0
    # visualize results
    vis_bgr = cv2.cvtColor(image_rgb, cv2.COLOR_RGB2BGR) if len(image_rgb.shape)==3 else cv2.cvtColor(image_rgb, cv2.COLOR_GRAY2BGR)
    # draw ROI and lane center
    h, w = binary.shape
    start = int(h*(1-roi_ratio))
    cv2.rectangle(vis_bgr, (0, start), (w, h), (0, 255, 255), 2)
    rows, cols = np.where(binary[start:, :] == 255)
    if len(rows) > 0:
        lane_center = int(np.mean(cols))
        cv2.line(vis_bgr, (lane_center, start), (lane_center, h), (255, 0, 0), 2)
        cv2.line(vis_bgr, (w//2, start), (w//2, h), (0, 255, 0), 2)
    # draw steering arrow
    if angle != 0:
        draw_arrow(vis_bgr, angle)
    # convert back to RGB for matplotlib display
    vis_rgb = cv2.cvtColor(vis_bgr, cv2.COLOR_BGR2RGB)
    return vis_rgb, offset, angle

def show_images(images,cmap=None):
    column =  2
    rows = (len(images)+1) // column
    plt.figure(figsize=(10,11))
    for i,image in enumerate(images):
        plt.subplot(rows,column,i+1)
        effective_cmap = 'gray' if len(image.shape) == 2 else cmap
        plt.imshow(image,cmap=effective_cmap)
        plt.axis('off')
    plt.tight_layout(pad=0.0,w_pad=0.0,h_pad=0.0)
    plt.show()
    
def show_contrast_images(original_images,processed_images,method='threshold'):
    column=2
    rows = (len(original_images)+1) // column
    plt.figure(figsize=(10,11))
    for i,(orig,proc) in enumerate(zip(original_images,processed_images)):
        plt.subplot(rows,column,i*2+1)
        plt.imshow(orig)
        plt.title('Original')
        plt.axis('off')
        
        plt.subplot(rows,column,i*2+2)
        cmap = 'gray' if len(proc.shape) == 2 else None
        plt.imshow(proc,cmap=cmap)
        plt.title(f'Processed ({method})')
        plt.axis('off')
    plt.tight_layout(pad=0.0,w_pad=0.0,h_pad=0.0)
    plt.show()


def binarize_lane(image_rgb, method='threshold', threshold_value=200):
    # type check and normalization
    if image_rgb.dtype != np.uint8:
        if image_rgb.max() <= 1.0:
            image_rgb = (image_rgb * 255).astype(np.uint8)
        else:
            image_rgb = image_rgb.astype(np.uint8)
    
    # convert to grayscale
    gray = cv2.cvtColor(image_rgb, cv2.COLOR_RGB2GRAY)
    
    if method == 'threshold':
        _, binary = cv2.threshold(gray, threshold_value, 255, cv2.THRESH_BINARY)
    elif method == 'canny':
        blurred = cv2.GaussianBlur(gray, (5, 5), 0)
        edges = cv2.Canny(blurred, 50, 150)
        binary = edges
    else:
        raise ValueError("method must be 'threshold' or 'canny'")
    return binary

def calculate_lane_offset(binary,roi_ratio=0.33):
    h,w=binary.shape
    start=int(h*(1-roi_ratio))
    roi=binary[start:h,0:w]
    rows,cols=np.where(roi==255)
    if len(rows)==0:
        return None
    lane_center=np.mean(cols)
    image_center=w/2
    offset=lane_center-image_center
    return offset

def visualize_lane_center(image_rgb,binary,roi_ratio=0.33):
    h,w=binary.shape
    start=int(h*(1-roi_ratio))
    vis=image_rgb.copy()
    if len(image_rgb.shape)==2:
        vis=cv2.cvtColor(vis,cv2.COLOR_GRAY2RGB) #make sure it's 3-channel for visualization
    rows,cols=np.where(binary[start:h,0:w]==255)
    cv2.rectangle(vis,(0,start),(w,h),(255,255,0),2) #draw ROI rectangle
    if len(rows)>0:
        lane_center=int(np.mean(cols))
        cv2.line(vis,(lane_center,start),(lane_center,h),(0,0,255),2) ##draw lane center
        cv2.line(vis,(w//2,start),(w//2,h),(0,255,0),2) #draw image center
    return vis

print(os.getcwd())
os.chdir(r'C:\Users\JohnTsang\Desktop\MyProject\LKA')
test_images = [plt.imread(path) for path in glob.glob('test_images/*.png')]
binary_images = [binarize_lane(img,method='threshold',threshold_value=200) for img in test_images]
binary_images_canny = [binarize_lane(img,method='canny') for img in test_images]
show_contrast_images(test_images,binary_images,method='threshold')
show_contrast_images(test_images,binary_images_canny,method='canny')
print([calculate_lane_offset(img) for img in binary_images])
visualized_images = [visualize_lane_center(img,binary) for img,binary in zip(test_images,binary_images)]
show_images(visualized_images)
pid = PIDController(kp=0.15, kd=0.05)

for img in test_images:
    vis, offset, angle = process_pipeline(img, method='threshold', pid=pid)
    if offset is not None:
        print(f"Offset: {offset:.1f} px, Steering: {angle:.1f}°")
    else:
        print("No lane detected.")
    plt.imshow(vis)
    plt.axis('off')
    plt.show()

cap = cv2.VideoCapture('test_video.mp4')
fps = cap.get(cv2.CAP_PROP_FPS) if cap.get(cv2.CAP_PROP_FPS) > 0 else 30.0
pid = PIDController(kp=0.15, kd=0.05)
while True:
    ret, frame_bgr = cap.read()
    if not ret: break
    frame_rgb = cv2.cvtColor(frame_bgr, cv2.COLOR_BGR2RGB)
    vis, offset, angle = process_pipeline(frame_rgb, pid=pid,dt=1/fps)
    # display results
    cv2.imshow('Lane Following', cv2.cvtColor(vis, cv2.COLOR_RGB2BGR))
    if cv2.waitKey(1) & 0xFF == ord('q'): break
cap.release()
cv2.destroyAllWindows()