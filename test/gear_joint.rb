gen = lambda do
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  phase = 0.1
  ratio = 0.2
  Chipmunk2d::GearJoint.new(a, b, phase, ratio)
end

assert('Chipmunk2d::GearJoint type') do
  assert_kind_of(Class, Chipmunk2d::GearJoint)
end

assert('Chipmunk2d::GearJoint#initialize') do
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  phase = 0.1
  ratio = 0.2
  constraint = Chipmunk2d::GearJoint.new(a, b, phase, ratio)
  assert_kind_of(Chipmunk2d::Constraint, constraint)
  assert_kind_of(Chipmunk2d::GearJoint, constraint)
  assert_equal(a, constraint.body_a)
  assert_equal(b, constraint.body_b)
  assert_float(phase, constraint.phase)
  assert_float(ratio, constraint.ratio)
end

assert('Chipmunk2d::GearJoint#phase') do
  c = gen.call
  assert_kind_of(Float, c.phase)
  c.phase = 0.5
  assert_float(0.5, c.phase)
end

assert('Chipmunk2d::GearJoint#ratio') do
  c = gen.call
  assert_kind_of(Float, c.ratio)
  c.ratio = 0.3
  assert_float(0.3, c.ratio)
end
