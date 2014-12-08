def assert_vect_equal(a, b)
  msg = 'Expected to be equal' unless msg
  diff = assertion_diff(a, b)
  assert_true(a.fuzzy_eql?(b), msg, diff)
end

assert('Chipmunk2d::Transform type') do
  assert_kind_of(Class, Chipmunk2d::Transform)
end

assert('Chipmunk2d::Transform#initialize') do
  t = Chipmunk2d::Transform.new(1.0, 0.8, 0.5, 0.6, 0.2, 0.3)
  assert_kind_of(Chipmunk2d::Transform, t)
  assert_float(1.0, t.a)
  assert_float(0.8, t.b)
  assert_float(0.5, t.c)
  assert_float(0.6, t.d)
  assert_float(0.2, t.tx)
  assert_float(0.3, t.ty)
end

assert('Chipmunk2d::Transform#a') do
  t = Chipmunk2d::Transform.new(1.0, 0.8, 0.5, 0.6, 0.2, 0.3)
  assert_kind_of(Float, t.a)
  t.a = 0.0
  assert_float(0.0, t.a)
  assert_float(0.8, t.b)
  assert_float(0.5, t.c)
  assert_float(0.6, t.d)
  assert_float(0.2, t.tx)
  assert_float(0.3, t.ty)
end

assert('Chipmunk2d::Transform#b') do
  t = Chipmunk2d::Transform.new(1.0, 0.8, 0.5, 0.6, 0.2, 0.3)
  assert_kind_of(Float, t.b)
  t.b = 0.0
  assert_float(1.0, t.a)
  assert_float(0.0, t.b)
  assert_float(0.5, t.c)
  assert_float(0.6, t.d)
  assert_float(0.2, t.tx)
  assert_float(0.3, t.ty)
end

assert('Chipmunk2d::Transform#c') do
  t = Chipmunk2d::Transform.new(1.0, 0.8, 0.5, 0.6, 0.2, 0.3)
  assert_kind_of(Float, t.c)
  t.c = 0.0
  assert_float(1.0, t.a)
  assert_float(0.8, t.b)
  assert_float(0.0, t.c)
  assert_float(0.6, t.d)
  assert_float(0.2, t.tx)
  assert_float(0.3, t.ty)
end

assert('Chipmunk2d::Transform#d') do
  t = Chipmunk2d::Transform.new(1.0, 0.8, 0.5, 0.6, 0.2, 0.3)
  assert_kind_of(Float, t.d)
  t.d = 0.0
  assert_float(1.0, t.a)
  assert_float(0.8, t.b)
  assert_float(0.5, t.c)
  assert_float(0.0, t.d)
  assert_float(0.2, t.tx)
  assert_float(0.3, t.ty)
end

assert('Chipmunk2d::Transform#tx') do
  t = Chipmunk2d::Transform.new(1.0, 0.8, 0.5, 0.6, 0.2, 0.3)
  assert_kind_of(Float, t.tx)
  t.tx = 0.0
  assert_float(1.0, t.a)
  assert_float(0.8, t.b)
  assert_float(0.5, t.c)
  assert_float(0.6, t.d)
  assert_float(0.0, t.tx)
  assert_float(0.3, t.ty)
end

assert('Chipmunk2d::Transform#ty') do
  t = Chipmunk2d::Transform.new(1.0, 0.8, 0.5, 0.6, 0.2, 0.3)
  assert_kind_of(Float, t.ty)
  t.ty = 0.0
  assert_float(1.0, t.a)
  assert_float(0.8, t.b)
  assert_float(0.5, t.c)
  assert_float(0.6, t.d)
  assert_float(0.2, t.tx)
  assert_float(0.0, t.ty)
end

assert('Chipmunk2d::Transform#inverse') do
  t = Chipmunk2d::Transform.new(1.0, 0.8, 0.5, 0.6, 0.2, 0.3)
  result = t.inverse
  assert_kind_of(Chipmunk2d::Transform, result)
  assert_float(3.0, result.a)
  assert_float(-4.0, result.b)
  assert_float(-2.5, result.c)
  assert_float(5.0, result.d)
  assert_float(0.15, result.tx)
  assert_float(-0.7, result.ty)
end

assert('Chipmunk2d::Transform#point') do
  t = Chipmunk2d::Transform.new(1.0, 0.8, 0.5, 0.6, 0.2, 0.3)
  p = Chipmunk2d::Vect.new(2, 3)
  result = t.point(p)
  assert_kind_of(Chipmunk2d::Vect, result)
  assert_vect_equal(Chipmunk2d::Vect.new(3.7, 3.7), result)
end

assert('Chipmunk2d::Transform#vect') do
  t = Chipmunk2d::Transform.new(1.0, 0.8, 0.5, 0.6, 0.2, 0.3)
  result = t.vect(Chipmunk2d::Vect.new(0.5, 0.4))
  assert_kind_of(Chipmunk2d::Vect, result)
  assert_vect_equal(Chipmunk2d::Vect.new(0.7, 0.640), result)
end

assert('Chipmunk2d::Transform#bb') do
  t = Chipmunk2d::Transform.new(1.0, 0.8, 0.5, 0.6, 0.2, 0.3)
  result = t.bb(Chipmunk2d::BB.new(1, 1, 5, 5))
  assert_kind_of(Chipmunk2d::BB, result)
  assert_float(1.7, result.l)
  assert_float(1.7, result.b)
  assert_float(7.7, result.r)
  assert_float(7.3, result.t)
end

assert('Chipmunk2d::Transform#rigid_inverse') do
  t = Chipmunk2d::Transform.new(1.0, 0.8, 0.5, 0.6, 0.2, 0.3)
  result = t.rigid_inverse
  assert_kind_of(Chipmunk2d::Transform, result)
  assert_float(0.6, result.a)
  assert_float(-0.8, result.b)
  assert_float(-0.5, result.c)
  assert_float(1.0, result.d)
  assert_float(0.03, result.tx)
  assert_float(-0.14, result.ty)
end

assert('Chipmunk2d::Transform#wrap') do
  t = Chipmunk2d::Transform.new(1.0, 0.8, 0.5, 0.6, 0.2, 0.3)
  a = Chipmunk2d::Transform.new(0.0, 0.4, 0.2, 0.8, 0.5, 1.0)
  result = t.wrap(a)
  assert_kind_of(Chipmunk2d::Transform, result)
  assert_float(-2.120, result.a)
  assert_float(4.56, result.b)
  assert_float(-1.34, result.c)
  assert_float(2.92, result.d)
  assert_float(-1.47, result.tx)
  assert_float(3.66, result.ty)
end

assert('Chipmunk2d::Transform#wrap_inverse') do
  t = Chipmunk2d::Transform.new(1.0, 0.8, 0.5, 0.6, 0.2, 0.3)
  a = Chipmunk2d::Transform.new(0.0, 0.4, 0.2, 0.8, 0.5, 1.0)
  result = t.wrap_inverse(a)
  assert_kind_of(Chipmunk2d::Transform, result)
  assert_float(-1.8, result.a)
  assert_float(-1.84, result.b)
  assert_float(2.5, result.c)
  assert_float(2.6, result.d)
  assert_float(0.81, result.tx)
  assert_float(0.888, result.ty)
end

assert('Chipmunk2d::Transform.new_transpose') do
  t = Chipmunk2d::Transform.new_transpose(1.0, 0.8, 0.5, 0.6, 0.2, 0.3)
  assert_kind_of(Chipmunk2d::Transform, t)
end

assert('Chipmunk2d::Transform.translate') do
  t = Chipmunk2d::Transform.translate(Chipmunk2d::Vect.new(2, 5))
  assert_kind_of(Chipmunk2d::Transform, t)
end

assert('Chipmunk2d::Transform.scale') do
  t = Chipmunk2d::Transform.scale(0.4, 0.3)
  assert_kind_of(Chipmunk2d::Transform, t)
end

assert('Chipmunk2d::Transform.rotate') do
  t = Chipmunk2d::Transform.rotate(1.28)
  assert_kind_of(Chipmunk2d::Transform, t)
end

assert('Chipmunk2d::Transform.rigid') do
  t = Chipmunk2d::Transform.rigid(Chipmunk2d::Vect.new(2, 5), 1.28)
  assert_kind_of(Chipmunk2d::Transform, t)
end

assert('Chipmunk2d::Transform.ortho') do
  t = Chipmunk2d::Transform.ortho(Chipmunk2d::BB.new(1, 2, 7, 8))
  assert_kind_of(Chipmunk2d::Transform, t)
end

assert('Chipmunk2d::Transform.bone_scale') do
  t = Chipmunk2d::Transform.bone_scale(Chipmunk2d::Vect.new(1, 2), Chipmunk2d::Vect.new(4, 6))
  assert_kind_of(Chipmunk2d::Transform, t)
end

assert('Chipmunk2d::Transform.axial_scale') do
  t = Chipmunk2d::Transform.axial_scale(Chipmunk2d::Vect.new(1, 2),
                                        Chipmunk2d::Vect.new(4, 6),
                                        0.6)
  assert_kind_of(Chipmunk2d::Transform, t)
end
