// Auto-generated. Do not edit!

// (in-package ros_melodic_test.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class VisualOdometryMsg {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.cam_in_map_pose = null;
      this.translation_weight = null;
      this.rotation_weight = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('cam_in_map_pose')) {
        this.cam_in_map_pose = initObj.cam_in_map_pose
      }
      else {
        this.cam_in_map_pose = new geometry_msgs.msg.Pose();
      }
      if (initObj.hasOwnProperty('translation_weight')) {
        this.translation_weight = initObj.translation_weight
      }
      else {
        this.translation_weight = 0.0;
      }
      if (initObj.hasOwnProperty('rotation_weight')) {
        this.rotation_weight = initObj.rotation_weight
      }
      else {
        this.rotation_weight = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VisualOdometryMsg
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [cam_in_map_pose]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.cam_in_map_pose, buffer, bufferOffset);
    // Serialize message field [translation_weight]
    bufferOffset = _serializer.float64(obj.translation_weight, buffer, bufferOffset);
    // Serialize message field [rotation_weight]
    bufferOffset = _serializer.float64(obj.rotation_weight, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VisualOdometryMsg
    let len;
    let data = new VisualOdometryMsg(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [cam_in_map_pose]
    data.cam_in_map_pose = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    // Deserialize message field [translation_weight]
    data.translation_weight = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [rotation_weight]
    data.rotation_weight = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 72;
  }

  static datatype() {
    // Returns string type for a message object
    return 'ros_melodic_test/VisualOdometryMsg';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f17e00e8d06ef5c890124246d0e4b633';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Header header
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new VisualOdometryMsg(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.cam_in_map_pose !== undefined) {
      resolved.cam_in_map_pose = geometry_msgs.msg.Pose.Resolve(msg.cam_in_map_pose)
    }
    else {
      resolved.cam_in_map_pose = new geometry_msgs.msg.Pose()
    }

    if (msg.translation_weight !== undefined) {
      resolved.translation_weight = msg.translation_weight;
    }
    else {
      resolved.translation_weight = 0.0
    }

    if (msg.rotation_weight !== undefined) {
      resolved.rotation_weight = msg.rotation_weight;
    }
    else {
      resolved.rotation_weight = 0.0
    }

    return resolved;
    }
};

module.exports = VisualOdometryMsg;
