fn main() {
    println!("Hello, world!");
}

fn likes(names: &[&str]) -> String {
    let who = match names.len() {
        0 => "no one".to_owned(),
        1 => names[0].to_owned(),
        2 => format!("{} and {}", names[0], names[1]),
        3 => format!("{}, {} and {}", names[0], names[1], names[2]),
        _ => format!("{}, {} and {} others", names[0], names[1], names.len() - 2),
    };

    let like = if names.len() <= 1 { "likes" } else { "like" };

    format!("{} {} this", who, like)
}

#[test]
fn example_tests() {
    assert_eq!(likes(&[]), "no one likes this");
    assert_eq!(likes(&["Peter"]), "Peter likes this");
    assert_eq!(likes(&["Jacob", "Alex"]), "Jacob and Alex like this");
    assert_eq!(
        likes(&["Max", "John", "Mark"]),
        "Max, John and Mark like this"
    );
    assert_eq!(
        likes(&["Alex", "Jacob", "Mark", "Max"]),
        "Alex, Jacob and 2 others like this"
    );
}
