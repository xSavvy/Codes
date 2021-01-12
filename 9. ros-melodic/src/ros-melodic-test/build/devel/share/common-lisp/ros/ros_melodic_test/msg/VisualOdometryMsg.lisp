; Auto-generated. Do not edit!


(cl:in-package ros_melodic_test-msg)


;//! \htmlinclude VisualOdometryMsg.msg.html

(cl:defclass <VisualOdometryMsg> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (cam_in_map_pose
    :reader cam_in_map_pose
    :initarg :cam_in_map_pose
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose))
   (translation_weight
    :reader translation_weight
    :initarg :translation_weight
    :type cl:float
    :initform 0.0)
   (rotation_weight
    :reader rotation_weight
    :initarg :rotation_weight
    :type cl:float
    :initform 0.0))
)

(cl:defclass VisualOdometryMsg (<VisualOdometryMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VisualOdometryMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VisualOdometryMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_melodic_test-msg:<VisualOdometryMsg> is deprecated: use ros_melodic_test-msg:VisualOdometryMsg instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <VisualOdometryMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_melodic_test-msg:header-val is deprecated.  Use ros_melodic_test-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'cam_in_map_pose-val :lambda-list '(m))
(cl:defmethod cam_in_map_pose-val ((m <VisualOdometryMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_melodic_test-msg:cam_in_map_pose-val is deprecated.  Use ros_melodic_test-msg:cam_in_map_pose instead.")
  (cam_in_map_pose m))

(cl:ensure-generic-function 'translation_weight-val :lambda-list '(m))
(cl:defmethod translation_weight-val ((m <VisualOdometryMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_melodic_test-msg:translation_weight-val is deprecated.  Use ros_melodic_test-msg:translation_weight instead.")
  (translation_weight m))

(cl:ensure-generic-function 'rotation_weight-val :lambda-list '(m))
(cl:defmethod rotation_weight-val ((m <VisualOdometryMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_melodic_test-msg:rotation_weight-val is deprecated.  Use ros_melodic_test-msg:rotation_weight instead.")
  (rotation_weight m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VisualOdometryMsg>) ostream)
  "Serializes a message object of type '<VisualOdometryMsg>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'cam_in_map_pose) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'translation_weight))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'rotation_weight))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VisualOdometryMsg>) istream)
  "Deserializes a message object of type '<VisualOdometryMsg>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'cam_in_map_pose) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'translation_weight) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rotation_weight) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VisualOdometryMsg>)))
  "Returns string type for a message object of type '<VisualOdometryMsg>"
  "ros_melodic_test/VisualOdometryMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VisualOdometryMsg)))
  "Returns string type for a message object of type 'VisualOdometryMsg"
  "ros_melodic_test/VisualOdometryMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VisualOdometryMsg>)))
  "Returns md5sum for a message object of type '<VisualOdometryMsg>"
  "f17e00e8d06ef5c890124246d0e4b633")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VisualOdometryMsg)))
  "Returns md5sum for a message object of type 'VisualOdometryMsg"
  "f17e00e8d06ef5c890124246d0e4b633")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VisualOdometryMsg>)))
  "Returns full string definition for message of type '<VisualOdometryMsg>"
  (cl:format cl:nil "std_msgs/Header header~%geometry_msgs/Pose cam_in_map_pose~%float64 translation_weight~%float64 rotation_weight~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VisualOdometryMsg)))
  "Returns full string definition for message of type 'VisualOdometryMsg"
  (cl:format cl:nil "std_msgs/Header header~%geometry_msgs/Pose cam_in_map_pose~%float64 translation_weight~%float64 rotation_weight~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VisualOdometryMsg>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'cam_in_map_pose))
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VisualOdometryMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'VisualOdometryMsg
    (cl:cons ':header (header msg))
    (cl:cons ':cam_in_map_pose (cam_in_map_pose msg))
    (cl:cons ':translation_weight (translation_weight msg))
    (cl:cons ':rotation_weight (rotation_weight msg))
))
