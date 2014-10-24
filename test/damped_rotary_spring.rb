assert('Chipmunk2d::DampedRotarySpring#initialize') do
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  rest_angle = 0.1
  stiffness = 1.0
  damping = 0.01
  constraint = Chipmunk2d::DampedRotarySpring.new(a, b, rest_angle, stiffness, damping)
  assert_kind_of(Chipmunk2d::Constraint, constraint)
  assert_kind_of(Chipmunk2d::DampedRotarySpring, constraint)
  assert_equal(a, constraint.body_a)
  assert_equal(b, constraint.body_b)
  assert_equal(rest_angle, constraint.rest_angle)
  assert_equal(stiffness, constraint.stiffness)
  assert_equal(damping, constraint.damping)
end
