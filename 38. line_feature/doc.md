<!--
 * @Author: Liu Weilong
 * @Date: 2021-03-09 10:31:43
 * @LastEditors: Liu Weilong 
 * @LastEditTime: 2021-03-09 17:27:09
 * @FilePath: /3rd-test-learning/38. line_feature/doc.md
 * @Description: 
-->
### 测试

图片标准 752 480
测试端 PC

(空)|Edgelet|Common Line|Vanishing
---|---|---|---
提取|a. Gaussian+ScharrXY+Canny 30ms|a. 直接LSD(opencv) 50ms<br>b. LSD(Custom) 0.5倍缩放 12.5ms(extract) + 4ms(des)<br> c. fld 17ms|a. VanishingPointDetection(3rdParty) 70ms
匹配|a. 直接光流匹配|a. LSD(Custom) 0.5倍缩放 0.1ms(match) |
优化|a. 光流优化|a. plucker 4自由度优化|
优点|a. 不容易被遮挡<br> b. 提取速度应该可以加速<br>|a. 普遍性|
缺点|a. Aperture Problem|a. 容易被遮挡<br>b. 容易被截断导致匹配不上|

### 备注

序号|Edgelet|Common Line|Vanishing
---|---|---|---
1. ||光流端点匹配尝试一下？|
2. ||LSD+L1|
3. ||FLD 转 LBD需要的格式|

