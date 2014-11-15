gen = lambda do
  # why a GearJoint you ask, because I just felt like it...
  Chipmunk2d::GearJoint.new(Chipmunk2d::Body.new_static, Chipmunk2d::Body.new_kinematic, 0.1, 0.5)
end

assert('Chipmunk2d::Constraint type') do
  assert_kind_of(Class, Chipmunk2d::Constraint)
end

assert('Chipmunk2d::Constraint#initialize should fail') do
  # now, under normal circumstances, you're not suppose to create a Constraint.
  assert_raise(RuntimeError) do
    Chipmunk2d::Constraint.new
  end
end

assert('Chipmunk2d::Constraint#space') do
  constraint = gen.call
  sp = Chipmunk2d::Space.new
  assert_equal(nil, constraint.space)
  sp.add_constraint(constraint)
  space = constraint.space
  assert_kind_of(Chipmunk2d::Space, space)
  assert_equal(sp, space)
end

assert('Chipmunk2d::Constraint#body_a') do
  constraint = gen.call
  body_a = constraint.body_a
  assert_kind_of(Chipmunk2d::Body, body_a)
end

assert('Chipmunk2d::Constraint#body_b') do
  constraint = gen.call
  body_b = constraint.body_b
  assert_kind_of(Chipmunk2d::Body, body_b)
end

assert('Chipmunk2d::Constraint#max_force') do
  constraint = gen.call
  max_force = constraint.max_force
  assert_kind_of(Float, max_force)
  assert_float(0.0, max_force)
end

assert('Chipmunk2d::Constraint#error_bias') do
  constraint = gen.call
  error_bias = constraint.error_bias
  assert_kind_of(Float, error_bias)
  #assert_float(0.0, error_bias)
end

assert('Chipmunk2d::Constraint#max_bias') do
  constraint = gen.call
  max_bias = constraint.max_bias
  assert_kind_of(Float, max_bias)
  assert_float(0.0, max_bias)
end

assert('Chipmunk2d::Constraint#collide_bodies') do
  constraint = gen.call
  collide_bodies = constraint.collide_bodies
  #assert_kind_of(Boolean, collide_bodies) # ruby/mruby, y u no haz Boolean?
  assert_equal(true, collide_bodies)
end

assert('Chipmunk2d::Constraint#impulse') do
  constraint = gen.call
  impulse = constraint.impulse
  assert_kind_of(Float, impulse)
  assert_float(0.0, impulse)
end
