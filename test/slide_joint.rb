def assert_vect_equal(a, b)
  msg = 'Expected to be equal' unless msg
  diff = assertion_diff(a, b)
  assert_true(a.fuzzy_eql?(b), msg, diff)
end

gen = lambda do
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  anchor_a = Chipmunk2d::Vect.new(1.0, 2.3)
  anchor_b = Chipmunk2d::Vect.new(0.1, 0)
  min = 0.6
  max = 0.3
  Chipmunk2d::SlideJoint.new(a, b, anchor_a, anchor_b, min, max)
end

assert('Chipmunk2d::SlideJoint type') do
  assert_kind_of(Class, Chipmunk2d::SlideJoint)
end

assert('Chipmunk2d::SlideJoint#initialize') do
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  anchor_a = Chipmunk2d::Vect.new(1.0, 2.3)
  anchor_b = Chipmunk2d::Vect.new(0.1, 0)
  min = 0.6
  max = 0.3
  joint = Chipmunk2d::SlideJoint.new(a, b, anchor_a, anchor_b, min, max)
  assert_kind_of(Chipmunk2d::Constraint, joint)
  assert_kind_of(Chipmunk2d::SlideJoint, joint)
  assert_equal(a, joint.body_a)
  assert_equal(b, joint.body_b)
  assert_equal(anchor_a, joint.anchor_a)
  assert_equal(anchor_b, joint.anchor_b)
  assert_equal(min, joint.min)
  assert_equal(max, joint.max)
end

assert('Chipmunk2d::SlideJoint#anchor_a') do
  j = gen.call
  assert_kind_of(Chipmunk2d::Vect, j.anchor_a)
  v = Chipmunk2d::Vect.new(1, 0)
  j.anchor_a = v
  assert_vect_equal(v, j.anchor_a)
end

assert('Chipmunk2d::SlideJoint#anchor_b') do
  j = gen.call
  assert_kind_of(Chipmunk2d::Vect, j.anchor_b)
  v = Chipmunk2d::Vect.new(1, 0)
  j.anchor_b = v
  assert_vect_equal(v, j.anchor_b)
end

assert('Chipmunk2d::SlideJoint#min') do
  j = gen.call
  assert_kind_of(Float, j.min)
  j.min = 0.1
  assert_float(0.1, j.min)
end

assert('Chipmunk2d::SlideJoint#max') do
  j = gen.call
  assert_kind_of(Float, j.max)
  j.max = 0.7
  assert_float(0.7, j.max)
end
