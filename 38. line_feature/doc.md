<!--
 * @Author: Liu Weilong
 * @Date: 2021-03-08 16:15:02
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-08 16:53:53
 * @FilePath: /3rd-test-learning/38. line_feature/doc.md
 * @Description: 
-->

图片标准 752 480
测试端 PC

(空)|Edgelet|Common Line|Vanishing
---|---|---|---
提取|a. Gaussian+ScharrXY+Canny 30ms|a. 直接LSD 50ms<br>b. 因为边相对长一些，所以可以压缩，压缩到0.4倍之后10ms|
匹配|a. 直接光流匹配|a. |
优化|a. 光流优化||
