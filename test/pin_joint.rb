def assert_vect_equal(a, b)
  msg = 'Expected to be equal' unless msg
  diff = assertion_diff(a, b)
  assert_true(a.fuzzy_eql?(b), msg, diff)
end

gen = lambda do
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  anchor_a = Chipmunk2d::Vect.new(1, 0)
  anchor_b = Chipmunk2d::Vect.new(-1, 1)
  Chipmunk2d::PinJoint.new(a, b, anchor_a, anchor_b)
end

assert('Chipmunk2d::PinJoint type') do
  assert_kind_of(Class, Chipmunk2d::PinJoint)
end

assert('Chipmunk2d::PinJoint#initialize') do
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  anchor_a = Chipmunk2d::Vect.new(1, 0)
  anchor_b = Chipmunk2d::Vect.new(-1, 1)
  joint = Chipmunk2d::PinJoint.new(a, b, anchor_a, anchor_b)
  assert_kind_of(Chipmunk2d::Constraint, joint)
  assert_kind_of(Chipmunk2d::PinJoint, joint)
  assert_equal(a, joint.body_a)
  assert_equal(b, joint.body_b)
  assert_equal(anchor_a, joint.anchor_a)
  assert_equal(anchor_b, joint.anchor_b)
end


assert('Chipmunk2d::PinJoint#anchor_a') do
  c = gen.call
  assert_kind_of(Chipmunk2d::Vect, c.anchor_a)
  v = Chipmunk2d::Vect.new(12, 8)
  c.anchor_a = v
  assert_vect_equal(v, c.anchor_a)
end

assert('Chipmunk2d::PinJoint#anchor_b') do
  c = gen.call
  assert_kind_of(Chipmunk2d::Vect, c.anchor_b)
  v = Chipmunk2d::Vect.new(12, 8)
  c.anchor_b = v
  assert_vect_equal(v, c.anchor_b)
end

assert('Chipmunk2d::PinJoint#dist') do
  c = gen.call
  assert_kind_of(Float, c.dist)
  c.dist = 0.7
  assert_float(0.7, c.dist)
  c.dist = 1.7
  assert_float(1.7, c.dist)
end
