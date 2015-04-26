def assert_vect_equal(a, b)
  msg = 'Expected to be equal' unless msg
  diff = assertion_diff(a, b)
  assert_true(a.fuzzy_eql?(b), msg, diff)
end

assert('Chipmunk2d::Vect type') do
  assert_kind_of(Class, Chipmunk2d::Vect)
end

assert('Chipmunk2d::Vect#initialize') do
  vect = Chipmunk2d::Vect.new(12, 12)
  assert_kind_of(Chipmunk2d::Vect, vect)
end

assert('Chipmunk2d::Vect#==') do
  vect1 = Chipmunk2d::Vect.new(12, 12)
  vect2 = Chipmunk2d::Vect.new(12, 12)
  vect3 = Chipmunk2d::Vect.new(5, 1)

  assert_equal(vect1, vect2)
  assert_not_equal(vect1, vect3)
end

assert('Chipmunk2d::Vect#x') do
  a = Chipmunk2d::Vect.new(0, 10)
  assert_kind_of(Float, a.x)
  assert_equal(0, a.x)
  assert_equal(10, a.y)
  a.x = 7
  assert_equal(7, a.x)
  assert_equal(10, a.y)
end

assert('Chipmunk2d::Vect#y') do
  a = Chipmunk2d::Vect.new(10, 0)
  assert_kind_of(Float, a.y)
  assert_float(10, a.x)
  assert_float(0, a.y)
  a.y = 7
  assert_float(10, a.x)
  assert_float(7, a.y)
end

assert('Chipmunk2d::Vect#+@') do
  a = Chipmunk2d::Vect.new(-1, 2)
  b = +a
  assert_kind_of(Chipmunk2d::Vect, b)
  assert_equal(a, b)
end

assert('Chipmunk2d::Vect#-@') do
  a = Chipmunk2d::Vect.new(-1, 2)
  b = -a
  assert_kind_of(Chipmunk2d::Vect, b)
  assert_float(1, b.x)
  assert_float(-2, b.y)
end

assert('Chipmunk2d::Vect#+') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(3, 4)
  c = a + b
  assert_kind_of(Chipmunk2d::Vect, c)
  assert_float(4, c.x)
  assert_float(6, c.y)
end

assert('Chipmunk2d::Vect#-') do
  a = Chipmunk2d::Vect.new(3, 7)
  b = Chipmunk2d::Vect.new(2, 4)
  c = a - b
  assert_kind_of(Chipmunk2d::Vect, c)
  assert_float(1, c.x)
  assert_float(3, c.y)
end

assert('Chipmunk2d::Vect#*') do
  a = Chipmunk2d::Vect.new(3, 2)
  b = 4
  c = a * b
  assert_kind_of(Chipmunk2d::Vect, c)
  assert_float(12, c.x)
  assert_float(8, c.y)
end

assert('Chipmunk2d::Vect#dot') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(3, 4)
  c = a.dot(b)
  assert_kind_of(Float, c)
  assert_float(11, c)
end

assert('Chipmunk2d::Vect#cross') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(3, 4)
  c = a.cross(b)
  assert_kind_of(Float, c)
  assert_float(-2, c)
end

assert('Chipmunk2d::Vect#perp') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = a.perp
  expected = Chipmunk2d::Vect.new(-2.0, 1.0)
  assert_kind_of(Chipmunk2d::Vect, b)
  assert_vect_equal(expected, b)
end

assert('Chipmunk2d::Vect#rperp') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = a.rperp
  expected = Chipmunk2d::Vect.new(2.0, -1.0)
  assert_kind_of(Chipmunk2d::Vect, b)
  assert_vect_equal(expected, b)
end

assert('Chipmunk2d::Vect#project') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(3, 5)
  c = a.project(b)
  expected = Chipmunk2d::Vect.new(1.14705882352941, 1.91176470588235)
  assert_kind_of(Chipmunk2d::Vect, c)
  assert_vect_equal(expected, c)
end

assert('Chipmunk2d::Vect#to_angle') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = a.to_angle
  assert_kind_of(Float, b)
  assert_float(1.10714871779409, b)
end

assert('Chipmunk2d::Vect#rotate') do
  a = Chipmunk2d::Vect.new(0.4, 0.2)
  b = Chipmunk2d::Vect.new(0.6, 0.3)
  c = a.rotate(b)
  expected = Chipmunk2d::Vect.new(0.17999999999999, 0.23999999999999)
  assert_kind_of(Chipmunk2d::Vect, c)
  assert_vect_equal(expected, c)
end

assert('Chipmunk2d::Vect#unrotate') do
  a = Chipmunk2d::Vect.new(0.4, 0.2)
  b = Chipmunk2d::Vect.new(0.6, 0.3)
  c = a.unrotate(b)
  expected = Chipmunk2d::Vect.new(0.3, 0.0)
  assert_kind_of(Chipmunk2d::Vect, c)
  assert_vect_equal(expected, c)
end

assert('Chipmunk2d::Vect#length_sq') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = a.length_sq
  assert_kind_of(Float, b)
  assert_float(5.0, b)
end

assert('Chipmunk2d::Vect#length') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = a.length
  assert_kind_of(Float, b)
  assert_float(2.23606797749978, b)
end

assert('Chipmunk2d::Vect#lerp') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(11, 12)
  c = a.lerp(b, 0.3)
  expected = Chipmunk2d::Vect.new(4, 5)
  assert_kind_of(Chipmunk2d::Vect, c)
  assert_vect_equal(expected, c)
end

assert('Chipmunk2d::Vect#normalize') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = a.normalize
  expected = Chipmunk2d::Vect.new(0.44721359549995, 0.89442719099991)
  assert_kind_of(Chipmunk2d::Vect, b)
  assert_vect_equal(expected, b)
end

assert('Chipmunk2d::Vect#slerp') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(11, 12)
  c = a.slerp(b, 0.3)
  expected = Chipmunk2d::Vect.new(4.04374503455712, 5.05194137017678)
  assert_kind_of(Chipmunk2d::Vect, c)
  assert_vect_equal(expected, c)
end

assert('Chipmunk2d::Vect#slerp_const') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(11, 12)
  c = a.slerp_const(b, 0.05)
  expected = Chipmunk2d::Vect.new(2.82501931250778, 3.83076940268812)
  assert_kind_of(Chipmunk2d::Vect, c)
  assert_vect_equal(expected, c)
end

assert('Chipmunk2d::Vect#clamp') do
  a = Chipmunk2d::Vect.new(1, 2)
  c = a.clamp(2)
  expected = Chipmunk2d::Vect.new(0.89442719099991, 1.78885438199983)
  assert_kind_of(Chipmunk2d::Vect, c)
  assert_vect_equal(expected, c)
end

assert('Chipmunk2d::Vect#lerp_const') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(11, 12)
  c = a.lerp_const(b, 0.3)
  expected = Chipmunk2d::Vect.new(1.21213203435596, 2.21213203435596)
  assert_kind_of(Chipmunk2d::Vect, c)
  assert_vect_equal(expected, c)
end

assert('Chipmunk2d::Vect#dist') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(11, 12)
  c = a.dist(b)
  assert_kind_of(Float, c)
  assert_float(14.1421356237309, c)
end

assert('Chipmunk2d::Vect#dist_sq') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(11, 12)
  c = a.dist_sq(b)
  assert_kind_of(Float, c)
  assert_float(200, c)
end

assert('Chipmunk2d::Vect#near?') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(11, 12)
  c = a.near?(b, 0.8)
  assert_equal(false, c)
end

assert('Chipmunk2d::Vect.for_angle') do
  a = Chipmunk2d::Vect.for_angle(1.7)
  expected = Chipmunk2d::Vect.new(-0.12884449429552, 0.99166481045246)
  assert_kind_of(Chipmunk2d::Vect, a)
  assert_vect_equal(expected, a)
end
