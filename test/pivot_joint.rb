assert('Chipmunk2d::PivotJoint type') do
  assert_kind_of(Class, Chipmunk2d::PivotJoint)
end

assert('Chipmunk2d::PivotJoint#initialize') do
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  anchor_a = Chipmunk2d::Vect.new(1, 0)
  anchor_b = Chipmunk2d::Vect.new(-1, 1)
  joint = Chipmunk2d::PivotJoint.new(a, b, anchor_a, anchor_b)
  assert_kind_of(Chipmunk2d::Constraint, joint)
  assert_kind_of(Chipmunk2d::PivotJoint, joint)
  assert_equal(a, joint.body_a)
  assert_equal(b, joint.body_b)
  assert_equal(anchor_a, joint.anchor_a)
  assert_equal(anchor_b, joint.anchor_b)
end
