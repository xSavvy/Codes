// Generated by gencpp from file ros_melodic_test/VisualOdometryMsg.msg
// DO NOT EDIT!


#ifndef ROS_MELODIC_TEST_MESSAGE_VISUALODOMETRYMSG_H
#define ROS_MELODIC_TEST_MESSAGE_VISUALODOMETRYMSG_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <geometry_msgs/Pose.h>

namespace ros_melodic_test
{
template <class ContainerAllocator>
struct VisualOdometryMsg_
{
  typedef VisualOdometryMsg_<ContainerAllocator> Type;

  VisualOdometryMsg_()
    : header()
    , cam_in_map_pose()
    , translation_weight()
    , rotation_weight()  {
    }
  VisualOdometryMsg_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , cam_in_map_pose(_alloc)
    , translation_weight(_alloc)
    , rotation_weight(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::geometry_msgs::Pose_<ContainerAllocator>  _cam_in_map_pose_type;
  _cam_in_map_pose_type cam_in_map_pose;

   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _translation_weight_type;
  _translation_weight_type translation_weight;

   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _rotation_weight_type;
  _rotation_weight_type rotation_weight;





  typedef boost::shared_ptr< ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator> const> ConstPtr;

}; // struct VisualOdometryMsg_

typedef ::ros_melodic_test::VisualOdometryMsg_<std::allocator<void> > VisualOdometryMsg;

typedef boost::shared_ptr< ::ros_melodic_test::VisualOdometryMsg > VisualOdometryMsgPtr;
typedef boost::shared_ptr< ::ros_melodic_test::VisualOdometryMsg const> VisualOdometryMsgConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator1> & lhs, const ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.cam_in_map_pose == rhs.cam_in_map_pose &&
    lhs.translation_weight == rhs.translation_weight &&
    lhs.rotation_weight == rhs.rotation_weight;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator1> & lhs, const ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace ros_melodic_test

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "08f7daef14ac52fffbd9100899ee6aef";
  }

  static const char* value(const ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x08f7daef14ac52ffULL;
  static const uint64_t static_value2 = 0xfbd9100899ee6aefULL;
};

template<class ContainerAllocator>
struct DataType< ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ros_melodic_test/VisualOdometryMsg";
  }

  static const char* value(const ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "std_msgs/Header header\n"
"geometry_msgs/Pose cam_in_map_pose\n"
"float64[] translation_weight\n"
"float64[] rotation_weight\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Pose\n"
"# A representation of pose in free space, composed of position and orientation. \n"
"Point position\n"
"Quaternion orientation\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Point\n"
"# This contains the position of a point in free space\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Quaternion\n"
"# This represents an orientation in free space in quaternion form.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"float64 w\n"
;
  }

  static const char* value(const ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.cam_in_map_pose);
      stream.next(m.translation_weight);
      stream.next(m.rotation_weight);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct VisualOdometryMsg_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ros_melodic_test::VisualOdometryMsg_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "cam_in_map_pose: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose_<ContainerAllocator> >::stream(s, indent + "  ", v.cam_in_map_pose);
    s << indent << "translation_weight[]" << std::endl;
    for (size_t i = 0; i < v.translation_weight.size(); ++i)
    {
      s << indent << "  translation_weight[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.translation_weight[i]);
    }
    s << indent << "rotation_weight[]" << std::endl;
    for (size_t i = 0; i < v.rotation_weight.size(); ++i)
    {
      s << indent << "  rotation_weight[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.rotation_weight[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROS_MELODIC_TEST_MESSAGE_VISUALODOMETRYMSG_H
