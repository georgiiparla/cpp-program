pipeline {
    agent any

    environment {
        FILE_NAME = 'program-foo-bar'

        ARTIFACT_ID = 'core'
        ZIP_NAME = 'core_ws.zip'
        BASE_VERSION = '1.0'

        NEXUS_URL = '172.20.10.25:8081'
        NEXUS_CREDENTIALS_ID = '7d196d2f-f3c1-4803-bde9-2d17d18776b3'
        NEXUS_GROUP_ID = 'CS-Katana-lin/main'
        NEXUS_REPO = 'cpp-releases'
    }

    stages {
        
        stage ('Build Executable') {
            steps {
                echo "Compiling C++ source files..."
                sh "g++ -I main/ main/*.cpp -o ${FILE_NAME}"
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
                sh "zip ${ZIP_NAME} ${FILE_NAME}"
            }
        }

        stage('Publish to Nexus') {
            steps {
                script {
                    def snapshotVersion = "${BASE_VERSION}.${BUILD_NUMBER}"
                    echo "Uploading artifact version ${snapshotVersion} to ${NEXUS_REPO}..."
                
                    nexusArtifactUploader(
                        nexusVersion: 'nexus3',
                        protocol: 'http',
                        nexusUrl: "${NEXUS_URL}",
                        credentialsId: "${NEXUS_CREDENTIALS_ID}",
                        repository: "${NEXUS_REPO}",
                    
                        groupId: "${NEXUS_GROUP_ID}",
                        version: "${snapshotVersion}",
                    
                        artifacts: [
                            [
                                artifactId: "${ARTIFACT_ID}",
                                classifier: '',
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




