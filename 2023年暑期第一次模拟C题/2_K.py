import networkx as nx
import matplotlib.pyplot as plt

# 假设节点坐标和距离已经获取
node_coordinates = [(1, 1), (2, 2), (3, 3), (4, 4)]
distance_threshold = 2.0  # 距离阈值，小于该距离将建立连边

# 创建图
graph = nx.Graph()

def calculate_distance(coord1, coord2):
    """
    计算两个节点之间的距离
    :param coord1: 节点1坐标
    :param coord2: 节点2坐标
    :return: 两个节点之间的距离
    """
    return ((coord1[0] - coord2[0]) ** 2 + (coord1[1] - coord2[1]) ** 2) ** 0.5

# 添加节点
for i, coord in enumerate(node_coordinates):
    graph.add_node(i, pos=coord)

# 构建连边
for i in range(len(node_coordinates)):
    for j in range(i + 1, len(node_coordinates)):
        distance = calculate_distance(node_coordinates[i], node_coordinates[j])
        if distance < distance_threshold:
            graph.add_edge(i, j)

# 绘制图像
pos = nx.get_node_attributes(graph, 'pos')
nx.draw(graph, pos, with_labels=True, node_size=500, font_size=10, font_color='black')
plt.show()
