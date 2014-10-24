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
  assert_equal(min, joint.min)
  assert_equal(max, joint.max)
end
