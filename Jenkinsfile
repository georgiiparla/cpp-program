pipeline {
    agent any

    environment {
        ARTIFACT_NAME   = 'my-program'
        ZIP_NAME        = 'cpp-build.zip'
        BASE_VERSION    = '1.0'

        NEXUS_URL           = '172.20.10.25:8081'
        NEXUS_CREDENTIALS_ID= '7d196d2f-f3c1-4803-bde9-2d18776b3'
        NEXUS_REPO          = 'cpp-releases'
        NEXUS_GROUP_ID      = 'rs2.georgii-parla.cpp-programs'
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
                echo "Uploading artifact to Nexus..."
                nexusArtifactUploader(
                    nexusVersion: 'nexus3',
                    protocol: 'http',
                    nexusUrl: "${NEXUS_URL}",
                    credentialsId: "${NEXUS_CREDENTIALS_ID}",
                    
                    groupId: "${NEXUS_GROUP_ID}",
                    artifactId: "${ARTIFACT_NAME}",
                    version: "${BASE_VERSION}.${BUILD_NUMBER}",
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

        stage ('Deploy'){
            steps {
                echo 'Deploying...'
            }
        }
    }
}