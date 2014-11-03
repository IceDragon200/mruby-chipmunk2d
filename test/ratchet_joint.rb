@test_pi = (22 / 7.0)

def make_test_ratchet_joint
  a = Chipmunk2d::Body.new(100, 1)
  b = Chipmunk2d::Body.new(100, 1)
  phase   = 0.5
  ratchet = @test_pi * 2
  Chipmunk2d::RatchetJoint.new(a, b, phase, ratchet)
end

assert('Chipmunk2d::RatchetJoint type') do
  assert_kind_of(Class, Chipmunk2d::RatchetJoint)
end

assert('Chipmunk2d::RatchetJoint#initialize') do
  ratchet_joint = make_test_ratchet_joint
  assert_kind_of(Chipmunk2d::RatchetJoint, ratchet_joint)
end

assert('Chipmunk2d::RatchetJoint#angle') do
  ratchet_joint = make_test_ratchet_joint
  assert_kind_of(Float, ratchet_joint.angle)
  assert_equal(0.0, ratchet_joint.angle)
  ratchet_joint.angle = @test_pi
  assert_equal(@test_pi, ratchet_joint.angle)
end

assert('Chipmunk2d::RatchetJoint#phase') do
  ratchet_joint = make_test_ratchet_joint
  assert_kind_of(Float, ratchet_joint.phase)
  assert_equal(0.5, ratchet_joint.phase)
  ratchet_joint.phase = @test_pi
  assert_equal(@test_pi, ratchet_joint.phase)
end

assert('Chipmunk2d::RatchetJoint#ratchet') do
  ratchet_joint = make_test_ratchet_joint
  assert_kind_of(Float, ratchet_joint.ratchet)
  assert_equal(@test_pi * 2, ratchet_joint.ratchet)
  ratchet_joint.ratchet = @test_pi
  assert_equal(@test_pi, ratchet_joint.ratchet)
end
