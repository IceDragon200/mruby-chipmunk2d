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
