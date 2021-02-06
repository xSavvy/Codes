<!--
 * @Author: Liu Weilong
 * @Date: 2021-02-04 15:39:23
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-02-04 15:57:32
 * @FilePath: /3rd-test-learning/doc/paper/paper-21.2.4-21.2.30/doc.md
 * @Description: 
-->
### SVO 再探
1. 匹配过程
   SparseImageAligned
   PyrDirectMethod 到三层左右停下来 进一步加速+鲁棒核 
   TrackLocalMap 抗光照模型也就是那个 -m 
   |___ Patch Affine + 图层判断
   |___ Edgelet 
2. Mapping
   Depth Filter
3. Motion Piror
   直接当作优化项写在SparseImageAligned里面
