module Chipmunk2d
  class BB
    # @return [String]
    def inspect
      # format isn't apart of the core mruby implementation, so I'll just
      # leave the id unconverted
      "<#{self.class}:#{__id__} l=#{l} b=#{b} r=#{r} t=#{t}>"
    end
  end
end
