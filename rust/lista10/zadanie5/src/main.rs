fn main() {}

fn print(n: i32) -> Option<String> {
    if n <= 0 || n % 2 == 0 {
        return None;
    }

    let mut diamond = String::new();

    for i in 0..=n / 2 {
        diamond.push_str(&generate_line(n, i));
    }

    for i in (0..n / 2).rev() {
        diamond.push_str(&generate_line(n, i));
    }

    Some(diamond)
}

fn generate_line(n: i32, i: i32) -> String {
    let spaces = n / 2 - i;
    let stars = 2 * i + 1;

    format!(
        "{}{}\n",
        " ".repeat(spaces as usize),
        "*".repeat(stars as usize)
    )
}

#[test]
fn basic_test() {
    assert_eq!(print(3), Some(" *\n***\n *\n".to_string()));
    assert_eq!(print(5), Some("  *\n ***\n*****\n ***\n  *\n".to_string()));
    assert_eq!(print(-3), None);
    assert_eq!(print(2), None);
    assert_eq!(print(0), None);
    assert_eq!(print(1), Some("*\n".to_string()));
}
