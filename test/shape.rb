assert('Chipmunk2d::CircleShape#initialize') do
  body = Chipmunk2d::Body.new(100, 1)
  radius = 5
  offset = Chipmunk2d::Vect.new(1, 1)
  shape = Chipmunk2d::CircleShape.new(body, radius, offset)
  assert_kind_of(Chipmunk2d::Shape, shape)
  assert_kind_of(Chipmunk2d::CircleShape, shape)
  assert_equal(body, shape.body)
  assert_equal(radius, shape.radius)
  assert_equal(offset, shape.offset)
end

assert('Chipmunk2d::SegmentShape#initialize') do
  body = Chipmunk2d::Body.new(100, 1)
  a = Chipmunk2d::Vect.new(0, 0)
  b = Chipmunk2d::Vect.new(1, 1)
  radius = 5
  shape = Chipmunk2d::SegmentShape.new(body, a, b, radius)
  assert_kind_of(Chipmunk2d::Shape, shape)
  assert_kind_of(Chipmunk2d::SegmentShape, shape)
  assert_equal(body, shape.body)
  assert_equal(a, shape.a)
  assert_equal(b, shape.b)
  assert_equal(radius, shape.radius)
end
