def assert_vect_equal(a, b)
  msg = 'Expected to be equal' unless msg
  diff = assertion_diff(a, b)
  assert_true(a.fuzzy_eql?(b), msg, diff)
end

# Chipmunk2d::Space core definitions
assert('Chipmunk2d::Space type') do
  assert_kind_of(Class, Chipmunk2d::Space)
end

assert('Chipmunk2d::Space#initialize') do
  space = Chipmunk2d::Space.new
  assert_kind_of(Chipmunk2d::Space, space)
end

assert('Chipmunk2d::Space#iterations') do
  space = Chipmunk2d::Space.new
  assert_kind_of(Integer, space.iterations)
  space.iterations = 4
  assert_equal(4, space.iterations)
end

assert('Chipmunk2d::Space#gravity') do
  space = Chipmunk2d::Space.new
  assert_kind_of(Chipmunk2d::Vect, space.gravity)
  space.gravity = Chipmunk2d::Vect.new(0, 1.1)
  assert_vect_equal(Chipmunk2d::Vect.new(0, 1.1), space.gravity)
end

assert('Chipmunk2d::Space#damping') do
  space = Chipmunk2d::Space.new
  assert_kind_of(Float, space.damping)
  space.damping = 1.1
  assert_float(1.1, space.damping)
end

assert('Chipmunk2d::Space#idle_speed_threshold') do
  space = Chipmunk2d::Space.new
  assert_kind_of(Float, space.idle_speed_threshold)
  space.idle_speed_threshold = 1.4
  assert_float(1.4, space.idle_speed_threshold)
end

assert('Chipmunk2d::Space#sleep_time_threshold') do
  space = Chipmunk2d::Space.new
  assert_kind_of(Float, space.sleep_time_threshold)
  space.sleep_time_threshold = 1.4
  assert_float(1.4, space.sleep_time_threshold)
end

assert('Chipmunk2d::Space#collision_slop') do
  space = Chipmunk2d::Space.new
  assert_kind_of(Float, space.collision_slop)
  space.collision_slop = 1.4
  assert_float(1.4, space.collision_slop)
end

assert('Chipmunk2d::Space#collision_bias') do
  space = Chipmunk2d::Space.new
  assert_kind_of(Float, space.collision_bias)
  space.collision_bias = 1.4
  assert_float(1.4, space.collision_bias)
end

assert('Chipmunk2d::Space#collision_persistence') do
  space = Chipmunk2d::Space.new
  assert_kind_of(Integer, space.collision_persistence)
  space.collision_persistence = 2
  assert_equal(2, space.collision_persistence)
end

# (IceDragon) TODO: Will fail unless static_body problem is fixed.
#assert('Chipmunk2d::Space#static_body') do
#  space = Chipmunk2d::Space.new
#  assert_kind_of(Chipmunk2d::Body, space.static_body)
#end

assert('Chipmunk2d::Space#current_time_step') do
  space = Chipmunk2d::Space.new
  assert_kind_of(Float, space.current_time_step)
end

assert('Chipmunk2d::Space#locked?') do
  space = Chipmunk2d::Space.new
  #assert_kind_of(Boolean, space.locked?)
  assert_equal(false, space.locked?)
end

assert('Chipmunk2d::Space#add_default_collision_handler') do
  space = Chipmunk2d::Space.new
  ch = space.add_default_collision_handler
  # (IceDragon) TODO
  #assert_kind_of(Chipmunk2d::CollisionHandler, ch)
  true
end

assert('Chipmunk2d::Space#add_collision_handler') do
  space = Chipmunk2d::Space.new
  ch = space.add_collision_handler(1, 2)
  # (IceDragon) TODO
  #assert_kind_of(Chipmunk2d::CollisionHandler, ch)
  true
end

assert('Chipmunk2d::Space#add_wildcard_handler') do
  space = Chipmunk2d::Space.new
  ch = space.add_wildcard_handler(1)
  # (IceDragon) TODO
  #assert_kind_of(Chipmunk2d::CollisionHandler, ch)
  true
end

assert('Chipmunk2d::Space shape') do
  space = Chipmunk2d::Space.new
  body = Chipmunk2d::Body.new(100, 1)
  shape = Chipmunk2d::CircleShape.new(body, 2, Chipmunk2d::Vect.new(0, 0))

  res = space.add_shape(shape)
  assert_kind_of(Chipmunk2d::Shape, res)
  assert_equal(shape, res)
  assert_true(space.contains_shape?(shape))

  res = space.remove_shape(shape)
  assert_kind_of(Chipmunk2d::Shape, res)
  assert_equal(shape, res)
  assert_false(space.contains_shape?(shape))
end

assert('Chipmunk2d::Space body') do
  space = Chipmunk2d::Space.new
  body = Chipmunk2d::Body.new(100, 1)
  shape = Chipmunk2d::CircleShape.new(body, 2, Chipmunk2d::Vect.new(0, 0))

  res = space.add_body(body)
  assert_kind_of(Chipmunk2d::Body, res)
  assert_equal(body, res)
  assert_true(space.contains_body?(body))

  res = space.remove_body(body)
  assert_kind_of(Chipmunk2d::Body, res)
  assert_equal(body, res)
  assert_false(space.contains_body?(body))
end

assert('Chipmunk2d::Space constraint') do
  space = Chipmunk2d::Space.new
  constraint = Chipmunk2d::GearJoint.new(Chipmunk2d::Body.new_static, Chipmunk2d::Body.new_kinematic, 0.1, 0.5)

  res = space.add_constraint(constraint)
  assert_kind_of(Chipmunk2d::Constraint, constraint)
  assert_equal(constraint, res)
  assert_true(space.contains_constraint?(constraint))

  res = space.remove_constraint(constraint)
  assert_kind_of(Chipmunk2d::Constraint, constraint)
  assert_equal(constraint, res)
  assert_false(space.contains_constraint?(constraint))
end

assert('Chipmunk2d::Space#add_post_step_callback') do
  space = Chipmunk2d::Space.new
  egg = 0
  space.add_post_step_callback(:my_callback) do |space|
    egg += 1
  end
  space.step(0.1)
  assert_equal(1, egg)
end

assert('Chipmunk2d::Space#point_query') do
  space = Chipmunk2d::Space.new
  b = Chipmunk2d::Body.new(100, 1)
  s = Chipmunk2d::CircleShape.new(b, 2, Chipmunk2d::Vect.zero)
  point = Chipmunk2d::Vect.new(0, 0)
  max_distance = 5
  filter = Chipmunk2d::ShapeFilter::ALL
  m = 1

  space.add_body(b)
  space.add_shape(s)
  space.point_query(point, max_distance, filter) do |shape, point, distance, gradient|
    assert_kind_of(Chipmunk2d::Shape, shape)
    assert_kind_of(Chipmunk2d::Vect, point)
    assert_kind_of(Float, distance)
    assert_kind_of(Chipmunk2d::Vect, gradient)
    assert_equal(s, shape)
    m -= 1
  end
  assert_equal(0, m)
  true
end

assert('Chipmunk2d::Space#point_query_nearest') do
  space = Chipmunk2d::Space.new
  b = Chipmunk2d::Body.new(100, 1)
  s = Chipmunk2d::CircleShape.new(b, 2, Chipmunk2d::Vect.zero)
  out = Chipmunk2d::PointQueryInfo.new
  point = Chipmunk2d::Vect.new(0, 0)
  max_distance = 5
  filter = Chipmunk2d::ShapeFilter::ALL

  space.add_body(b)
  space.add_shape(s)
  shape = space.point_query_nearest(point, max_distance, filter, out)
  assert_kind_of(Chipmunk2d::Shape, shape)
  true
end

assert('Chipmunk2d::Space#segment_query') do
  space = Chipmunk2d::Space.new
  # TODO
end

assert('Chipmunk2d::Space#segment_query_first') do
  space = Chipmunk2d::Space.new
  # TODO
end

assert('Chipmunk2d::Space#bb_query') do
  space = Chipmunk2d::Space.new
  # TODO
end

assert('Chipmunk2d::Space#shape_query') do
  space = Chipmunk2d::Space.new
  b = Chipmunk2d::Body.new(100, 1)
  s = Chipmunk2d::CircleShape.new(b, 2, Chipmunk2d::Vect.zero)

  space.add_body(b)
  space.add_shape(s)
  space.shape_query(s) do |shape, points|
    assert_kind_of(Chipmunk2d::Shape, shape)
    if points
      assert_kind_of(Chipmunk2d::ContactPointSet, points)
    end
  end
  true
end

assert('Chipmunk2d::Space#each_body') do
  space = Chipmunk2d::Space.new
  body = Chipmunk2d::Body.new(100, 1)
  space.add_body(body)
  m = 1
  space.each_body do |b|
    assert_kind_of(Chipmunk2d::Body, b)
    assert_equal(body, b)
    m -= 1
  end
  assert_equal(0, m)
  true
end

assert('Chipmunk2d::Space#each_shape') do
  space = Chipmunk2d::Space.new
  body = Chipmunk2d::Body.new(100, 1)
  shape = Chipmunk2d::CircleShape.new(body, 2, Chipmunk2d::Vect.new(0, 0))
  space.add_shape(shape)
  m = 1
  space.each_shape do |s|
    assert_kind_of(Chipmunk2d::Shape, s)
    assert_equal(shape, s)
    m -= 1
  end
  assert_equal(0, m)
  true
end

assert('Chipmunk2d::Space#each_constraint') do
  space = Chipmunk2d::Space.new
  constraint = Chipmunk2d::GearJoint.new(Chipmunk2d::Body.new_static, Chipmunk2d::Body.new_kinematic, 0.1, 0.5)
  space.add_constraint(constraint)
  m = 1
  space.each_constraint do |c|
    assert_kind_of(Chipmunk2d::Constraint, c)
    assert_equal(constraint, c)
    m -= 1
  end
  assert_equal(0, m)
  true
end

assert('Chipmunk2d::Space#reindex_static') do
  space = Chipmunk2d::Space.new
  space.add_body(Chipmunk2d::Body.new_static)
  space.add_body(Chipmunk2d::Body.new_static)
  space.add_body(Chipmunk2d::Body.new_static)
  space.reindex_static
  true
end

assert('Chipmunk2d::Space#reindex_shape') do
  space = Chipmunk2d::Space.new
  body = Chipmunk2d::Body.new(100, 1)
  shape = Chipmunk2d::CircleShape.new(body, 2, Chipmunk2d::Vect.new(0, 0))
  space.add_shape(shape)
  space.reindex_shape(shape)
  true
end

assert('Chipmunk2d::Space#reindex_shapes_for_body') do
  space = Chipmunk2d::Space.new
  body = Chipmunk2d::Body.new(100, 1)
  shape = Chipmunk2d::CircleShape.new(body, 2, Chipmunk2d::Vect.new(0, 0))
  space.add_shape(shape)
  space.add_body(body)
  space.reindex_shapes_for_body(body)
  true
end

assert('Chipmunk2d::Space#use_spatial_hash') do
  space = Chipmunk2d::Space.new
  space.use_spatial_hash(2.0, 4000)
  true
end

assert('Chipmunk2d::Space#step') do
  space = Chipmunk2d::Space.new
  space.step(0.1)
  true
end
