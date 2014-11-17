def assert_vect_equal(a, b)
  msg = 'Expected to be equal' unless msg
  diff = assertion_diff(a, b)
  assert_true(a.fuzzy_eql?(b), msg, diff)
end

assert('Chipmunk2d::Body type') do
  assert_kind_of(Class, Chipmunk2d::Body)
end

assert('Chipmunk2d::Body#initialize') do
  body = Chipmunk2d::Body.new(100, 1)
  assert_kind_of(Chipmunk2d::Body, body)
  assert_equal(body.mass, 100)
  assert_equal(body.moment, 1)
end

assert('Chipmunk2d::Body#destroy') do
  body = Chipmunk2d::Body.new(100, 1)
  body.destroy
end

assert('Chipmunk2d::Body#activate') do
  body = Chipmunk2d::Body.new(100, 1)
  body.activate
end

assert('Chipmunk2d::Body#activate_static') do
  bb = Chipmunk2d::BB.new(0, 0, 10, 10)
  radius = 5
  body = Chipmunk2d::Body.new(100, 1)
  body.type = Chipmunk2d::Body::TYPE_STATIC
  body2 = Chipmunk2d::Body.new(100, 1)
  shape = Chipmunk2d::BoxShape.new(body, bb, radius)
  shape2 = Chipmunk2d::BoxShape.new(body2, bb, radius)
  body.activate_static(shape2)
end

assert('Chipmunk2d::Body#sleep') do
  body = Chipmunk2d::Body.new(100, 1)
  space = Chipmunk2d::Space.new
  # bodies may not sleep without without a Space
  # else it segfaults...
  space.sleep_time_threshold = 1.1
  space.add_body(body)
  body.sleep
  # Chipmunk2d::Body#sleeping?
  assert_true(body.sleeping?)
end

assert('Chipmunk2d::Body#sleep_with_group') do
  group = Chipmunk2d::Body.new(10, 1)
  body = Chipmunk2d::Body.new(100, 1)
  space = Chipmunk2d::Space.new
  space.sleep_time_threshold = 1.1
  space.add_body(body)
  space.add_body(group)
  group.sleep
  body.sleep_with_group(group)
  # Chipmunk2d::Body#sleeping?
  assert_true(body.sleeping?)
end

assert('Chipmunk2d::Body#type') do
  body = Chipmunk2d::Body.new(100, 1)
  assert_kind_of(Integer, body.type)
  assert_equal(Chipmunk2d::Body::TYPE_DYNAMIC, body.type)
  body.type = Chipmunk2d::Body::TYPE_KINEMATIC
  assert_equal(Chipmunk2d::Body::TYPE_KINEMATIC, body.type)
end

assert('Chipmunk2d::Body#space') do
  body = Chipmunk2d::Body.new(100, 1)
  sp = Chipmunk2d::Space.new
  assert_equal(nil, body.space)
  sp.add_body(body)
  assert_kind_of(Chipmunk2d::Space, body.space)
  assert_equal(sp, body.space)
end

assert('Chipmunk2d::Body#mass') do
  body = Chipmunk2d::Body.new(100, 1)
  assert_kind_of(Float, body.mass)
  assert_float(100.0, body.mass)
  body.mass = 30
  assert_float(30.0, body.mass)
end

assert('Chipmunk2d::Body#moment') do
  body = Chipmunk2d::Body.new(100, 1)
  assert_kind_of(Float, body.moment)
  assert_float(1, body.moment)
  body.moment = 0.4
  assert_float(0.4, body.moment)
end

assert('Chipmunk2d::Body#position') do
  body = Chipmunk2d::Body.new(100, 1)
  assert_kind_of(Chipmunk2d::Vect, body.position)
  assert_equal(Chipmunk2d::Vect.zero, body.position)
end

assert('Chipmunk2d::Body#center_of_gravity') do
  body = Chipmunk2d::Body.new(100, 1)
  assert_kind_of(Chipmunk2d::Vect, body.center_of_gravity)
  assert_equal(Chipmunk2d::Vect.zero, body.center_of_gravity)
end

assert('Chipmunk2d::Body#velocity') do
  body = Chipmunk2d::Body.new(100, 1)
  assert_kind_of(Chipmunk2d::Vect, body.velocity)
  assert_equal(Chipmunk2d::Vect.zero, body.velocity)
end

assert('Chipmunk2d::Body#force') do
  body = Chipmunk2d::Body.new(100, 1)
  assert_kind_of(Chipmunk2d::Vect, body.force)
  assert_equal(Chipmunk2d::Vect.zero, body.force)
end

assert('Chipmunk2d::Body#angle') do
  body = Chipmunk2d::Body.new(100, 1)
  assert_kind_of(Float, body.angle)
  assert_float(0.0, body.angle)
end

assert('Chipmunk2d::Body#angular_velocity') do
  body = Chipmunk2d::Body.new(100, 1)
  assert_kind_of(Float, body.angular_velocity)
  assert_float(0.0, body.angular_velocity)
end

assert('Chipmunk2d::Body#torque') do
  body = Chipmunk2d::Body.new(100, 1)
  assert_kind_of(Float, body.torque)
  assert_float(0.0, body.torque)
end

assert('Chipmunk2d::Body#rotation') do
  body = Chipmunk2d::Body.new(100, 1)
  assert_kind_of(Chipmunk2d::Vect, body.rotation)
  assert_equal(Chipmunk2d::Vect.new(1, 0), body.rotation)
end

assert('Chipmunk2d::Body#local_to_world') do
  body = Chipmunk2d::Body.new(100, 1)
  point = Chipmunk2d::Vect.new(1, 2)
  result = body.local_to_world(point)
  assert_kind_of(Chipmunk2d::Vect, result)
end

assert('Chipmunk2d::Body#world_to_local') do
  body = Chipmunk2d::Body.new(100, 1)
  point = Chipmunk2d::Vect.new(1, 2)
  result = body.world_to_local(point)
  assert_kind_of(Chipmunk2d::Vect, result)
  assert_vect_equal(Chipmunk2d::Vect.new(1, 2), result)
end

assert('Chipmunk2d::Body#kinetic_energy') do
  body = Chipmunk2d::Body.new(100, 1)
  assert_kind_of(Float, body.kinetic_energy)
end

assert('Chipmunk2d::Body#each_shape') do
  body = Chipmunk2d::Body.new(100, 1)
  body.each_shape do |shape|
    assert_kind_of(Chipmunk2d::Shape, shape)
  end
end

assert('Chipmunk2d::Body#each_constraint') do
  body = Chipmunk2d::Body.new(100, 1)
  body.each_constraint do |constraint|
    assert_kind_of(Chipmunk2d::Constraint, constraint)
  end
end

assert('Chipmunk2d::Body#each_arbiter') do
  body = Chipmunk2d::Body.new(100, 1)
  body.each_arbiter do |arbiter|
    assert_kind_of(Chipmunk2d::Arbiter, arbiter)
  end
end
