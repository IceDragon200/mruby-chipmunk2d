def assert_vect_equal(a, b)
  msg = 'Expected to be equal' unless msg
  diff = assertion_diff(a, b)
  assert_true(a.fuzzy_eql?(b), msg, diff)
end

gen = lambda do
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  groove_a = Chipmunk2d::Vect.new(1, 0)
  groove_b = Chipmunk2d::Vect.new(1, 1)
  anchor_b = Chipmunk2d::Vect.new(-1, 1)
  Chipmunk2d::GrooveJoint.new(a, b, groove_a, groove_b, anchor_b)
end

assert('Chipmunk2d::GrooveJoint type') do
  assert_kind_of(Class, Chipmunk2d::GrooveJoint)
end

assert('Chipmunk2d::GrooveJoint#initialize') do
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  groove_a = Chipmunk2d::Vect.new(1, 0)
  groove_b = Chipmunk2d::Vect.new(1, 1)
  anchor_b = Chipmunk2d::Vect.new(-1, 1)
  joint = Chipmunk2d::GrooveJoint.new(a, b, groove_a, groove_b, anchor_b)
  assert_kind_of(Chipmunk2d::Constraint, joint)
  assert_kind_of(Chipmunk2d::GrooveJoint, joint)
  assert_equal(a, joint.body_a)
  assert_equal(b, joint.body_b)
  assert_equal(groove_a, joint.groove_a)
  assert_equal(groove_b, joint.groove_b)
  assert_equal(anchor_b, joint.anchor_b)
end

assert('Chipmunk2d::GrooveJoint#groove_a') do
  c = gen.call
  assert_kind_of(Chipmunk2d::Vect, c.groove_a)
  c.groove_a = Chipmunk2d::Vect.new(2, 3)
  assert_vect_equal(Chipmunk2d::Vect.new(2, 3), c.groove_a)
end

assert('Chipmunk2d::GrooveJoint#groove_b') do
  c = gen.call
  assert_kind_of(Chipmunk2d::Vect, c.groove_b)
  c.groove_b = Chipmunk2d::Vect.new(2, 3)
  assert_vect_equal(Chipmunk2d::Vect.new(2, 3), c.groove_b)
end

assert('Chipmunk2d::GrooveJoint#anchor_b') do
  c = gen.call
  assert_kind_of(Chipmunk2d::Vect, c.anchor_b)
  c.anchor_b = Chipmunk2d::Vect.new(2, 3)
  assert_vect_equal(Chipmunk2d::Vect.new(2, 3), c.anchor_b)
end
