pipeline {
    agent any

    // --- Central Configuration Block ---
    environment {
        // --- Project Configuration ---
        ARTIFACT_NAME   = 'my-program'
        ZIP_NAME        = 'cpp-build.zip'
        BASE_VERSION    = '1.0'

        // --- Nexus Configuration ---
        NEXUS_URL           = '172.20.10.25:8081'
        NEXUS_CREDENTIALS_ID= '7d196d2f-f3c1-4803-bde9-2d17d18776b3'
        NEXUS_GROUP_ID      = 'rs2.georgii-parla.cpp-programs'
        NEXUS_REPO          = 'cpp-releases' // The single target repository
    }

    stages {
        
        stage ('Build Executable') {
            steps {
                echo "Compiling C++ source files..."
                sh "g++ -I main/ main/*.cpp -o ${ARTIFACT_NAME}"
            }
        }

        stage ('Test'){
            steps {
                echo 'Testing...'
            }
        }

        stage('Package Artifact') {
            steps {
                echo "Packaging the executable into a ZIP archive..."
                sh "zip ${ZIP_NAME} ${ARTIFACT_NAME}"
            }
        }

        stage('Publish to Nexus') {
            steps {
                // Define the full version string for this build
                script {
                    def releaseVersion = "${BASE_VERSION}.${BUILD_NUMBER}"

                    echo "Uploading artifact version ${releaseVersion} to ${NEXUS_REPO}..."
                
                    nexusArtifactUploader(
                        nexusVersion: 'nexus3',
                        protocol: 'http',
                        nexusUrl: "${NEXUS_URL}",
                        credentialsId: "${NEXUS_CREDENTIALS_ID}",
                    
                        groupId: "${NEXUS_GROUP_ID}",
                        artifactId: "${ARTIFACT_NAME}",
                        version: "${releaseVersion}",
                        repository: "${NEXUS_REPO}",
                    
                        artifacts: [
                            [
                                file: "${ZIP_NAME}",
                                type: 'zip'
                            ]
                        ]
                    )
                }
            }
        }

        stage ('Deploy'){
            steps {
                echo 'Deploying...'
            }
        }
    }
}

