/// The bridge definition for our QObject
#[cxx_qt::bridge]
pub mod qobject {

    unsafe extern "C++" {
        include!("cxx-qt-lib/qstring.h");
        /// An alias to the QString type
        type QString = cxx_qt_lib::QString;
    }

    extern "RustQt" {
        // The QObject definition
        // We tell CXX-Qt that we want a QObject class with the name MyObject
        // based on the Rust struct MyObjectRust.
        #[qobject]
        #[qml_element]
        #[qproperty(i32, number)]
        #[qproperty(QString, string)]
        #[namespace = "my_object"]
        type MyObject = super::MyObjectRust;

        // Declare the invokable methods we want to expose on the QObject
        #[qinvokable]
        #[cxx_name = "incrementNumber"]
        fn increment_number(self: Pin<&mut Self>);

        #[qinvokable]
        #[cxx_name = "sayHi"]
        fn say_hi(&self, string: &QString, number: i32);

        #[qinvokable]
        #[cxx_name = "loadBook"]
        fn load_book(self: Pin<&mut Self>);

        #[qinvokable]
        #[cxx_name = "getBookHtml"]
        fn get_book_html(&self) -> QString;
    }
}

use core::pin::Pin;
use cxx_qt::CxxQtType;
use cxx_qt_lib::QString;
use rbook::{Epub, reader::ReaderContent};
use std::fs::File;

/// The Rust struct for the QObject
#[derive(Default)]
pub struct MyObjectRust {
    book: Option<Epub>,
    number: i32,
    string: QString,
}

impl qobject::MyObject {
    /// Increment the number Q_PROPERTY
    pub fn increment_number(self: Pin<&mut Self>) {
        let previous = *self.number();
        self.set_number(previous + 1);
    }

    pub fn load_book(mut self: Pin<&mut Self>) {
        let epub = Epub::open("test/romeo_and_juliet_pg1513_epub3.epub").unwrap();
        self.as_mut().rust_mut().book = Some(epub);
    }

    pub fn get_book_html(&self) -> QString {
        let mut html = String::new();
        if let Some(epub) = &self.book {
            // test to see if we can get css file names
            let manifest = epub.manifest();
            manifest.styles().for_each(|style| {
                println!("Style: {}", style.href_raw());
            });

            for data_result in epub.reader() {
                let data = data_result.unwrap();
                println!(
                    "Data ID: {} {}",
                    data.manifest_entry().id(),
                    data.spine_entry().id().unwrap_or("None")
                );
                let kind = data.manifest_entry().kind();
                html.push_str(data.content());
            }
        }
        let mut f = File::create("output.html").unwrap();
        std::io::Write::write_all(&mut f, html.as_bytes()).unwrap();
        html.into()
    }

    /// Print a log message with the given string and number
    pub fn say_hi(&self, string: &QString, number: i32) {
        println!("Hi from Rust! String is '{string}' and number is {number}");
    }
}
