# 手撕STL sort（基础版）
## 项目说明
本项目实现了STL sort的改进版：递归深度侦测切换堆排序 + 小阈值切换插入排序。理论上避免O(n²)退化，实践上严格按教材Hoare Partition和课堂堆排序实现。
包含depth_limit计算、Heap打印、Intermediate状态等调试输出。
## 如何运行
threshold=2 时，输入逆序数据即可看到Heap切换效果。
