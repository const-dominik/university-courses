class Integer
    def divisors
        divisors_tab = Array.new
        for i in 1..self/2 do
            if self % i == 0 then divisors_tab.push(i)
            end
        end
        divisors_tab.push(self)
    end

    def ack(y)
        if self == 0
            y+1
        elsif y == 0
            (self-1).ack(1)
        else
            (self-1).ack(self.ack(y-1))
        end
    end

    def perfect
        divisors = self.divisors
        divisors.pop
        divisors.sum == self
    end

    def slownie
        slowa = ["zero", "jeden", "dwa", "trzy", "cztery", "pięć", "sześć", "siedem", "osiem", "dziewięć"]
        result = self.abs().to_s.split("").map{ |num| slowa[num.to_i] }
        if self < 0 then result.unshift("minus") end
        result.join(" ")
    end        
end

puts "#{6.divisors}"
puts 2.ack(1)
puts 1.ack(2)
puts 1.perfect
puts 3.perfect
puts 6.perfect
puts -6.perfect
puts 10.perfect
puts -23.slownie
puts 0.slownie
puts 123.slownie
puts 1234567893124.slownie