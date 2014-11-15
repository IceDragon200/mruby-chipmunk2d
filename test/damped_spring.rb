gen = lambda do
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  anchor_a = Chipmunk2d::Vect.new(1, 1)
  anchor_b = Chipmunk2d::Vect.new(9, 9)
  rest_length = 3
  stiffness = 1.0
  damping = 0.01
  constraint = Chipmunk2d::DampedSpring.new(a, b, anchor_a, anchor_b, rest_length, stiffness, damping)
end

assert('Chipmunk2d::DampedSpring type') do
  assert_kind_of(Class, Chipmunk2d::DampedSpring)
end

assert('Chipmunk2d::DampedSpring#initialize') do
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  anchor_a = Chipmunk2d::Vect.new(1, 1)
  anchor_b = Chipmunk2d::Vect.new(9, 9)
  rest_length = 3
  stiffness = 1.0
  damping = 0.01
  constraint = Chipmunk2d::DampedSpring.new(a, b, anchor_a, anchor_b, rest_length, stiffness, damping)
  assert_kind_of(Chipmunk2d::Constraint, constraint)
  assert_kind_of(Chipmunk2d::DampedSpring, constraint)
  assert_equal(a, constraint.body_a)
  assert_equal(b, constraint.body_b)
  assert_equal(anchor_a, constraint.anchor_a)
  assert_equal(anchor_b, constraint.anchor_b)
  assert_equal(rest_length, constraint.rest_length)
  assert_equal(stiffness, constraint.stiffness)
  assert_equal(damping, constraint.damping)
end

assert('Chipmunk2d::DampedSpring#anchor_a') do
  constraint = gen.call
  Chipmunk2d::Vect.new(2, 3)
  assert_kind_of(constraint.anchor_a, Chipmunk2d::Vect)
  constraint.anchor_a = n
  assert_equal(n, constraint.anchor_a)
end

assert('Chipmunk2d::DampedSpring#anchor_b') do
  constraint = gen.call
  n = Chipmunk2d::Vect.new(10, 11)
  assert_kind_of(constraint.anchor_b, Chipmunk2d::Vect)
  constraint.anchor_b = n
  assert_equal(n, constraint.anchor_b)
end

assert('Chipmunk2d::DampedSpring#rest_length') do
  constraint = gen.call
  n = 11
  assert_kind_of(constraint.rest_length, Float)
  constraint.rest_length = n
  assert_equal(n, constraint.rest_length)
end

assert('Chipmunk2d::DampedSpring#stiffness') do
  constraint = gen.call
  n = 0.7
  assert_kind_of(constraint.stiffness, Float)
  constraint.stiffness = n
  assert_equal(n, constraint.stiffness)
end

assert('Chipmunk2d::DampedSpring#damping') do
  constraint = gen.call
  n = 0.2
  assert_kind_of(constraint.damping, Float)
  constraint.damping = n
  assert_equal(n, constraint.damping)
end
