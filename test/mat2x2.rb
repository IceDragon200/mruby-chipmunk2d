assert('Chipmunk2d::Mat2x2 type') do
  assert_kind_of(Class, Chipmunk2d::Mat2x2)
end

assert('Chipmunk2d::Mat2x2#initialize') do
  mat = Chipmunk2d::Mat2x2.new(1.0, 2.0, 3.0, 4.0)
  assert_kind_of(Chipmunk2d::Mat2x2, mat)
  assert_kind_of(Float, mat.a)
  assert_kind_of(Float, mat.b)
  assert_kind_of(Float, mat.c)
  assert_kind_of(Float, mat.d)
  assert_float(1.0, mat.a)
  assert_float(2.0, mat.b)
  assert_float(3.0, mat.c)
  assert_float(4.0, mat.d)
end

# attribute tests, make sure that changing one doesn't affect the others.
assert('Chipmunk2d::Mat2x2#a') do
  mat = Chipmunk2d::Mat2x2.new(1.0, 2.0, 3.0, 4.0)
  assert_float(1.0, mat.a)

  mat.a = 5.0
  assert_float(5.0, mat.a)
  assert_float(2.0, mat.b)
  assert_float(3.0, mat.c)
  assert_float(4.0, mat.d)
end

assert('Chipmunk2d::Mat2x2#b') do
  mat = Chipmunk2d::Mat2x2.new(1.0, 2.0, 3.0, 4.0)
  assert_float(2.0, mat.b)

  mat.b = 5.0
  assert_float(1.0, mat.a)
  assert_float(5.0, mat.b)
  assert_float(3.0, mat.c)
  assert_float(4.0, mat.d)
end

assert('Chipmunk2d::Mat2x2#c') do
  mat = Chipmunk2d::Mat2x2.new(1.0, 2.0, 3.0, 4.0)
  assert_float(3.0, mat.c)

  mat.c = 5.0
  assert_float(1.0, mat.a)
  assert_float(2.0, mat.b)
  assert_float(5.0, mat.c)
  assert_float(4.0, mat.d)
end

assert('Chipmunk2d::Mat2x2#d') do
  mat = Chipmunk2d::Mat2x2.new(1.0, 2.0, 3.0, 4.0)
  assert_float(4.0, mat.d)

  mat.d = 5.0
  assert_float(1.0, mat.a)
  assert_float(2.0, mat.b)
  assert_float(3.0, mat.c)
  assert_float(5.0, mat.d)
end

assert('Chipmunk2d::Mat2x2#transform') do
  mat = Chipmunk2d::Mat2x2.new(1.0, 1.0, 3.0, 3.0)
  vect = Chipmunk2d::Vect.new(4, 2)
  result = mat.transform(vect)
  assert_kind_of(Chipmunk2d::Vect, result)
  assert_float(6, result.x)
  assert_float(18, result.y)
end
