@test_pi = (22 / 7.0)

def make_test_rotary_limit_joint
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  min = -@test_pi
  max = @test_pi
  Chipmunk2d::RotaryLimitJoint.new(a, b, min, max)
end

assert('Chipmunk2d::RotaryLimitJoint type') do
  assert_kind_of(Class, Chipmunk2d::Body)
end

assert('Chipmunk2d::RotaryLimitJoint#initialize') do
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  min = -@test_pi
  max = @test_pi
  joint = Chipmunk2d::RotaryLimitJoint.new(a, b, min, max)
  assert_kind_of(Chipmunk2d::Constraint, joint)
  assert_kind_of(Chipmunk2d::RotaryLimitJoint, joint)
  assert_equal(a, joint.body_a)
  assert_equal(b, joint.body_b)
  assert_equal(min, joint.min)
  assert_equal(max, joint.max)
end

assert('Chipmunk2d::RotaryLimitJoint#angle') do
  joint = make_test_rotary_limit_joint
  assert_kind_of(Float, joint.min)
  assert_equal(-@test_pi, joint.min)
  joint.min = @test_pi
  assert_equal(@test_pi, joint.min)
end

assert('Chipmunk2d::RotaryLimitJoint#phase') do
  joint = make_test_rotary_limit_joint
  assert_kind_of(Float, joint.max)
  assert_equal(@test_pi, joint.max)
  joint.max = -@test_pi
  assert_equal(-@test_pi, joint.max)
end
