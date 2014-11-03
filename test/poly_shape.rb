assert('Chipmunk2d::PolyShape type') do
  assert_kind_of(Class, Chipmunk2d::PolyShape)
end

assert('Chipmunk2d::PolyShape#initialize(body, verts, radius)') do
  body = Chipmunk2d::Body.new(100, 1)
  verts = [Chipmunk2d::Vect.new(0, 0), Chipmunk2d::Vect.new(0, 1), Chipmunk2d::Vect.new(1, 0)]
  radius = 5
  shape = Chipmunk2d::PolyShape.new(body, verts, radius)
  assert_kind_of(Chipmunk2d::Shape, shape)
  assert_kind_of(Chipmunk2d::PolyShape, shape)
  assert_equal(body, shape.body)
end

assert('Chipmunk2d::PolyShape#initialize(body, verts, transform, radius)') do
  body = Chipmunk2d::Body.new(100, 1)
  verts = [Chipmunk2d::Vect.new(0, 0), Chipmunk2d::Vect.new(0, 1), Chipmunk2d::Vect.new(1, 0)]
  transform = Chipmunk2d::Transform.translate(Chipmunk2d::Vect.new(0, 0))
  radius = 5
  shape = Chipmunk2d::PolyShape.new(body, verts, transform, radius)
  assert_kind_of(Chipmunk2d::Shape, shape)
  assert_kind_of(Chipmunk2d::PolyShape, shape)
  assert_equal(body, shape.body)
  assert_equal(radius, shape.radius)
end
