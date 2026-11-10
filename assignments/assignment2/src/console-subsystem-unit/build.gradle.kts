plugins {
    application
}

repositories {
    mavenCentral()
}

dependencies {
    // Serial Arduino comm
    implementation("io.github.java-native:jssc:2.9.6")
}

java {
    toolchain {
        languageVersion = JavaLanguageVersion.of(21)
    }
}

application {
    // main class
    mainClass = "assignment2.Launcher"
}

//! -- exec -- //
tasks.named<JavaExec>("run") {
    standardInput = System.`in`
}
