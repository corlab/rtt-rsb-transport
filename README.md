RTT RSB Transport
=================

# Contents

This library provides an [RTT](http://www.orocos.org/rtt) transport
plugin for sending and receiving
[RST-RT](https://github.com/corlab/rst-rt) types to/from and
[RSB](https://code.cor-lab.org/projects/rsb) bus.

The code is heavily based on the rtt\_roscomm plugin in the
[rtt\_ros\_integration repository](https://github.com/orocos/rtt_ros_integration)
.

# Supported Types

| [RSB](https://code.cor-lab.org/projects/rsb) Type | [RTT](http://www.orocos.org/rtt) Type    |
|---------------------------------------------------|------------------------------------------|
| `rst.geometry.Translation`                        | `rstrt::geometry::Translation`           |
| `rst.geometry.Rotation`                        | `rstrt::geometry::Rotation`           |
| `rst.geometry.Pose`                        | `rstrt::geometry::Pose`           |
| `rst.kinematics.JointAngles`                      | `rstrt::kinematics::JointAngles`         |
| `rst.kinematics.JointVelocities`                  | `rstrt::kinematics::JointVelocities`     |
| `rst.kinematics.JointAccelerations`               | `rstrt::kinematics::JointAccelerations`  |
| `rst.kinematics.JointJerks`                       | `rstrt::kinematics::JointJerks`          |
| `rst.kinematics.LinearVelocities`                       | `rstrt::kinematics::LinearVelocities`          |
| `rst.kinematics.AngularVelocities`                       | `rstrt::geometry::AngularVelocity`          |
| `rst.kinematics.Twist`                       | `rstrt::kinematics::Twist`          |
| `rst.dynamics.JointTorques`                       | `rstrt::dynamics::JointTorques`          |
| `rst.dynamics.JointImpedance`                     | `rstrt::dynamics::JointImpedance`        |
| `rst.robot.JointState`                            | `rstrt::robot::JointState`               |
| `rst.robot.Weights`                               | `rstrt::robot::Weights`                  |
| `bool`                                            | `bool`                                   |
| `int64`                                           | `int`                                    |
| `uint64`                                          | `uint`                                   |
| `double`                                          | `double`                                 |
| `float`                                           | `float`                                  |
| `utf-8-string`                                    | `string`                                 |

# Plugins

## RSB Scopes

This plugin provides a global RTT service for creating connection
policies that establish RSB socket connections to specified scopes.

## RSB Socket Transport

This plugin provides (not yet) real-time-safe socket connections
between RSB scopes and Orocos RTT data ports.

# Usage

## Connecting an Orocos Port to an RSB Scope

```python
# Imports
import("rst-rt_typekit")
import("rtt_rsbcomm")

# Streaming
stream("my_component.my_output", rsb.transport.socket.scope("/my/output"))
stream("my_component.my_input", rsb.transport.socket.scope("/my/input"))
```

You can also set up these connections in C++ code:
```cpp
#include <rtt_rsbcomm/scope/ScopeService.hpp>

// ...

  // Add the port and stream it to a ROS topic
  this->ports()->addPort("my_port", my_port_);
  my_port_.createStream(rtt_rsbcomm::scope::scope("/my/scope"));

// ...
```
