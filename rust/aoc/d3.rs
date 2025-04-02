use std::fs;

#[derive(Debug)]
struct PartNumber {
    x1: i32,
    x2: i32,
    y: i32,
    num: i32,
}

#[derive(Debug)]
struct Symbol {
    x: i32,
    y: i32,
    val: char,
}

impl PartNumber {
    fn is_adjacent(&self, symbols: &[&Symbol]) -> bool {
        symbols.iter().any(|symbol| {
            (self.x1 - 1..=self.x2 + 1).contains(&symbol.x)
                && (self.y - 1..=self.y + 1).contains(&symbol.y)
        })
    }
}

fn parse_input(input: String) -> (Vec<PartNumber>, Vec<Symbol>) {
    let lines: Vec<&str> = input.split("\n").collect();
    let mut part_numbers: Vec<PartNumber> = vec![];
    let mut symbols: Vec<Symbol> = vec![];

    for (i, line) in lines.iter().enumerate() {
        let mut num = 0;
        let mut len = 0;
        for (j, c) in line.chars().enumerate() {
            if c.is_alphanumeric() {
                let digit = c.to_digit(10).unwrap() as i32;
                if len == 0 {
                    num = digit
                } else {
                    num *= 10;
                    num += digit;
                }
                len += 1;
            } else {
                if len > 0 {
                    part_numbers.push(PartNumber {
                        num: num,
                        x1: j as i32 - len,
                        x2: j as i32 - 1,
                        y: i as i32,
                    });
                    len = 0;
                }

                if c != '.' && c != '\n' && c != '\r' {
                    symbols.push(Symbol {
                        x: j as i32,
                        y: i as i32,
                        val: c,
                    })
                }
            }
        }
        if len > 0 {
            part_numbers.push(PartNumber {
                num: num,
                x1: line.len() as i32 - len,
                x2: line.len() as i32 - 1,
                y: i as i32,
            });
        }
    }

    (part_numbers, symbols)
}

fn main() {
    let input: String = fs::read_to_string("input.txt").unwrap();
    let (part_numbers, symbols) = parse_input(input);

    let symbols_refs: Vec<&Symbol> = symbols.iter().collect();
    let sum = part_numbers.iter().fold(0, |acc, p| {
        if p.is_adjacent(&symbols_refs) {
            acc + p.num
        } else {
            acc + 0
        }
    });

    let ratios: i32 = symbols
        .iter()
        .filter(|c| c.val == '*')
        .map(|symbol| {
            let mut gear_ratio = 1;
            let mut parts = 0;

            for p in &part_numbers {
                if p.is_adjacent(&[symbol]) {
                    gear_ratio *= p.num;
                    parts += 1;
                }
            }

            if parts == 2 {
                gear_ratio
            } else {
                0
            }
        })
        .sum();

    println!("{:?}", sum);
    println!("{:?}", ratios);
}
