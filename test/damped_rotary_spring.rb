gen = lambda do
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  rest_angle = 0.1
  stiffness = 1.0
  damping = 0.01
  constraint = Chipmunk2d::DampedRotarySpring.new(a, b, rest_angle, stiffness, damping)
end

assert('Chipmunk2d::DampedRotarySpring type') do
  assert_kind_of(Class, Chipmunk2d::DampedRotarySpring)
end

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

assert('Chipmunk2d::DampedRotarySpring#rest_angle') do
  c = gen.call
  assert_kind_of(Float, c.rest_angle)
  c.rest_angle = 3.14
  assert_float(3.14, c.rest_angle)
end

assert('Chipmunk2d::DampedRotarySpring#stiffness') do
  c = gen.call
  assert_kind_of(Float, c.stiffness)
  c.stiffness = 0.5
  assert_float(0.5, c.stiffness)
end

assert('Chipmunk2d::DampedRotarySpring#damping') do
  c = gen.call
  assert_kind_of(Float, c.damping)
  c.damping = 0.1
  assert_float(0.1, c.damping)
end
