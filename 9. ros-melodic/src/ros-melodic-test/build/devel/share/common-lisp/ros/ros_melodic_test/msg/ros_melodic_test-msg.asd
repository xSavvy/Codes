
(cl:in-package :asdf)

(defsystem "ros_melodic_test-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "VisualOdometryMsg" :depends-on ("_package_VisualOdometryMsg"))
    (:file "_package_VisualOdometryMsg" :depends-on ("_package"))
  ))