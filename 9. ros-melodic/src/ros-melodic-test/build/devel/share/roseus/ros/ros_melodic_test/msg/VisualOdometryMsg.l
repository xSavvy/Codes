;; Auto-generated. Do not edit!


(when (boundp 'ros_melodic_test::VisualOdometryMsg)
  (if (not (find-package "ROS_MELODIC_TEST"))
    (make-package "ROS_MELODIC_TEST"))
  (shadow 'VisualOdometryMsg (find-package "ROS_MELODIC_TEST")))
(unless (find-package "ROS_MELODIC_TEST::VISUALODOMETRYMSG")
  (make-package "ROS_MELODIC_TEST::VISUALODOMETRYMSG"))

(in-package "ROS")
;;//! \htmlinclude VisualOdometryMsg.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass ros_melodic_test::VisualOdometryMsg
  :super ros::object
  :slots (_header _cam_in_map_pose _translation_weight _rotation_weight ))

(defmethod ros_melodic_test::VisualOdometryMsg
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:cam_in_map_pose __cam_in_map_pose) (instance geometry_msgs::Pose :init))
    ((:translation_weight __translation_weight) 0.0)
    ((:rotation_weight __rotation_weight) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _cam_in_map_pose __cam_in_map_pose)
   (setq _translation_weight (float __translation_weight))
   (setq _rotation_weight (float __rotation_weight))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:cam_in_map_pose
   (&rest __cam_in_map_pose)
   (if (keywordp (car __cam_in_map_pose))
       (send* _cam_in_map_pose __cam_in_map_pose)
     (progn
       (if __cam_in_map_pose (setq _cam_in_map_pose (car __cam_in_map_pose)))
       _cam_in_map_pose)))
  (:translation_weight
   (&optional __translation_weight)
   (if __translation_weight (setq _translation_weight __translation_weight)) _translation_weight)
  (:rotation_weight
   (&optional __rotation_weight)
   (if __rotation_weight (setq _rotation_weight __rotation_weight)) _rotation_weight)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; geometry_msgs/Pose _cam_in_map_pose
    (send _cam_in_map_pose :serialization-length)
    ;; float64 _translation_weight
    8
    ;; float64 _rotation_weight
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; geometry_msgs/Pose _cam_in_map_pose
       (send _cam_in_map_pose :serialize s)
     ;; float64 _translation_weight
       (sys::poke _translation_weight (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rotation_weight
       (sys::poke _rotation_weight (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; geometry_msgs/Pose _cam_in_map_pose
     (send _cam_in_map_pose :deserialize buf ptr-) (incf ptr- (send _cam_in_map_pose :serialization-length))
   ;; float64 _translation_weight
     (setq _translation_weight (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rotation_weight
     (setq _rotation_weight (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get ros_melodic_test::VisualOdometryMsg :md5sum-) "f17e00e8d06ef5c890124246d0e4b633")
(setf (get ros_melodic_test::VisualOdometryMsg :datatype-) "ros_melodic_test/VisualOdometryMsg")
(setf (get ros_melodic_test::VisualOdometryMsg :definition-)
      "std_msgs/Header header
geometry_msgs/Pose cam_in_map_pose
float64 translation_weight
float64 rotation_weight
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

")



(provide :ros_melodic_test/VisualOdometryMsg "f17e00e8d06ef5c890124246d0e4b633")


