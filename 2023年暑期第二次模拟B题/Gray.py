import cv2

# 加载图片
image_path = 'test.jpg'
original_image = cv2.imread(image_path)

# 转换为灰度图
gray_image = cv2.cvtColor(original_image, cv2.COLOR_BGR2GRAY)

# 使用Canny边缘检测
edges = cv2.Canny(gray_image, threshold1=20, threshold2=60)  # 调整阈值以获得所需的边缘效果

# 显示Canny边缘检测图像
cv2.imwrite('Canny_Edges.jpg', edges)
cv2.imshow('Canny Edges', edges)
cv2.waitKey(0)
cv2.destroyAllWindows()
