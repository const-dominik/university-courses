use regex::Regex;
use std::collections::HashMap;
use std::fs;

fn get_steps(
    code_map: &HashMap<String, (String, String)>,
    directions: &Vec<char>,
    node: &str,
    is_2: bool,
) -> usize {
    let mut steps = 0;
    let mut current_node = node;

    while current_node != "ZZZ" {
        let (code1, code2) = code_map.get(current_node).unwrap();

        if directions[steps % directions.len()] == 'L' {
            current_node = code1;
        } else {
            current_node = code2;
        }
        println!("{}: {}", steps, current_node);
        steps += 1;

        if is_2 && current_node.ends_with("Z") {
            break;
        }
    }
    println!("{}: {}", current_node, current_node.ends_with("Z"));

    steps
}

fn gcd(a: usize, b: usize) -> usize {
    if b == 0 {
        return a;
    }

    gcd(b, a % b)
}

fn lcm(a: usize, b: usize) -> usize {
    a * b / gcd(a, b)
}

fn get_steps_2(code_map: &HashMap<String, (String, String)>, directions: &Vec<char>) -> usize {
    let start_nodes: Vec<&String> = code_map.keys().filter(|node| node.ends_with('A')).collect();

    let mut nodes_to_z: Vec<usize> = Vec::new();
    for node in start_nodes {
        nodes_to_z.push(get_steps(code_map, directions, node, true));
    }
// this works because the cycles are all the same length, which isn't mentioned in the problem
    nodes_to_z.iter().fold(1, |acc, x| lcm(acc, *x))
}

fn main() {
    let input = fs::read_to_string("input.txt").unwrap();
    let lines: Vec<&str> = input.split("\n").collect();

    let mut code_map: HashMap<String, (String, String)> = HashMap::new();
    let regex = Regex::new(r"^(\w+)\s=\s\((\w+)\,\s*(\w+)\)").unwrap();

    for line in &lines[2..lines.len()] {
        if let Some(captures) = regex.captures(line) {
            let key = captures[1].to_string();
            let code1 = captures[2].to_string();
            let code2 = captures[3].to_string();

            code_map.insert(key, (code1, code2));
        } else {
            eprintln!("Error parsing line: {}", line);
        }
    }

    let mut directions = lines[0].chars().collect::<Vec<char>>();
    directions.pop();

    println!("{:?}", get_steps(&code_map, &directions, &"AAA", false));
    println!("{:?}", get_steps_2(&code_map, &directions));
}
