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
  assert_equal(10, a.x)
  assert_equal(0, a.y)
  a.y = 7
  assert_equal(10, a.x)
  assert_equal(7, a.y)
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
  assert_equal(1, b.x)
  assert_equal(-2, b.x)
end

assert('Chipmunk2d::Vect#+') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(3, 4)
  c = a + b
  assert_kind_of(Chipmunk2d::Vect, c)
  assert_equal(4, c.x)
  assert_equal(6, c.y)
end

assert('Chipmunk2d::Vect#-') do
  a = Chipmunk2d::Vect.new(3, 7)
  b = Chipmunk2d::Vect.new(2, 4)
  c = a - b
  assert_kind_of(Chipmunk2d::Vect, c)
  assert_equal(1, c.x)
  assert_equal(3, c.y)
end

assert('Chipmunk2d::Vect#*') do
  a = Chipmunk2d::Vect.new(2, 2)
  b = Chipmunk2d::Vect.new(3, 4)
  c = a * b
  assert_kind_of(Chipmunk2d::Vect, c)
  assert_equal(6, c.x)
  assert_equal(8, c.y)
end

assert('Chipmunk2d::Vect#dot') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(3, 4)
  c = a.dot(b)
  assert_kind_of(Float, c)
  assert_equal(9, c)
end

assert('Chipmunk2d::Vect#cross') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(3, 4)
  c = a.cross(b)
  assert_kind_of(Float, c)
  # (IceDragon) TODO assert 'correct' value
  assert_equal(9, c)
end

assert('Chipmunk2d::Vect#perp') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = a.perp
  assert_kind_of(Chipmunk2d::Vect, b)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect#rperp') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = a.rperp
  assert_kind_of(Chipmunk2d::Vect, b)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect#project') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(3, 5)
  c = a.project(b)
  assert_kind_of(Chipmunk2d::Vect, c)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect#to_angle') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = a.to_angle
  assert_kind_of(Float, b)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect#rotate') do
  a = Chipmunk2d::Vect.new(0.4, 0.2)
  b = Chipmunk2d::Vect.new(0.6, 0.3)
  c = a.rotate(b)
  assert_kind_of(Chipmunk2d::Vect, c)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect#unrotate') do
  a = Chipmunk2d::Vect.new(0.4, 0.2)
  b = Chipmunk2d::Vect.new(0.6, 0.3)
  c = a.unrotate(b)
  assert_kind_of(Chipmunk2d::Vect, c)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect#length_sq') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = a.length_sq
  assert_kind_of(Float, b)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect#length') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = a.length
  assert_kind_of(Float, b)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect#lerp') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(11, 12)
  c = a.lerp(b, 0.3)
  assert_kind_of(Chipmunk2d::Vect, c)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect#normalize') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = a.normalize
  assert_kind_of(Chipmunk2d::Vect, b)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect#slerp') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(11, 12)
  c = a.slerp(b, 0.3)
  assert_kind_of(Chipmunk2d::Vect, c)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect#slerp_const') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(11, 12)
  c = a.slerp_const(b, 0.3)
  assert_kind_of(Chipmunk2d::Vect, c)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect#clamp') do
  a = Chipmunk2d::Vect.new(1, 2)
  c = a.clamp(2)
  assert_kind_of(Chipmunk2d::Vect, c)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect#lerp_const') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(11, 12)
  c = a.lerp_const(b, 0.3)
  assert_kind_of(Chipmunk2d::Vect, c)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect#dist') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(11, 12)
  c = a.dist(b)
  assert_kind_of(Float, c)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect#dist_sq') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(11, 12)
  c = a.dist_sq(b)
  assert_kind_of(Float, c)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect#near?') do
  a = Chipmunk2d::Vect.new(1, 2)
  b = Chipmunk2d::Vect.new(11, 12)
  c = a.near?(b, 0.8)
  assert_equal(true, c)
  # (IceDragon) TODO assert value
end

assert('Chipmunk2d::Vect.for_angle') do
  a = Chipmunk2d::Vect.for_angle(1.7)
  assert_kind_of(Chipmunk2d::Vect, a)
end
