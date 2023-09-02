import pandas as pd
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt

# 读取数据
data = pd.read_excel("第4题睡眠质量评价.xlsx")

# 提取特征列
features = data.iloc[:, :-1]

# 使用K-means算法进行聚类
kmeans = KMeans(n_clusters=4, random_state=42)
data['Cluster'] = kmeans.fit_predict(features)

# 绘制聚类图
plt.figure(figsize=(8, 6))
for cluster in data['Cluster'].unique():
    cluster_data = data[data['Cluster'] == cluster]
    plt.scatter(cluster_data['整晚睡眠时间小时制'], cluster_data['睡醒次数'], label=f'Cluster {cluster}')

# 添加图注
plt.legend(title='Clusters')
plt.xlabel('整晚睡眠时间（小时制）')
plt.ylabel('睡醒次数')
plt.title('睡眠质量评价 - K-means聚类')

plt.show()
